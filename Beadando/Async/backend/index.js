const express = require("express");
const cors = require("cors");
const app = express();
const PORT = 5000;

app.use(cors());
app.use(express.json());

// Teszadat generálása
const testData = Array.from({ length: 90000000 }, () =>
  Math.floor(Math.random() * 1000)
);

app.post("/calculate1", (req, res) => {
  const startTime = new Date().getTime();

  // Szekvenciális keresés a leggyakoribb elem megtalálására
  const sequentialSearch = (array) => {
    const frequency = {};
    let maxCount = 0;
    let mostFrequent;

    array.forEach((item) => {
      frequency[item] = (frequency[item] || 0) + 1;
      if (frequency[item] > maxCount) {
        maxCount = frequency[item];
        mostFrequent = item;
      }
    });

    return { number: mostFrequent, frequency: frequency[mostFrequent] };
  };

  // Párhuzamos keresés a leggyakoribb elem megtalálására
  const parallelSearch = (array) => {
    const frequency = {};
    let maxCount = 0;
    let mostFrequent;

    const promises = array.map((item) => {
      return new Promise((resolve) => {
        frequency[item] = (frequency[item] || 0) + 1;
        if (frequency[item] > maxCount) {
          maxCount = frequency[item];
          mostFrequent = item;
        }
        resolve();
      });
    });

    return Promise.all(promises).then(() => ({
      number: mostFrequent,
      frequency: frequency[mostFrequent],
    }));
  };

  // Teszadat generálása
  const testData = Array.from({ length: 150000 }, () =>
    Math.floor(Math.random() * 1000)
  );

  // Szekvenciális keresés és ideje
  const sequentialStartTime = new Date().getTime();
  const sequentialResult = sequentialSearch(testData);
  const sequentialEndTime = new Date().getTime();
  const sequentialExecutionTime = sequentialEndTime - sequentialStartTime;

  // Párhuzamos keresés és ideje
  const parallelStartTime = new Date().getTime();
  const parallelResultPromise = parallelSearch(testData);
  const parallelEndTime = new Date().getTime();
  const parallelExecutionTime = parallelEndTime - parallelStartTime;

  parallelResultPromise.then((parallelResult) => {
    const endTime = new Date().getTime();
    const executionTime = endTime - startTime;

    res.json({
      testData,
      sequentialResult,
      sequentialExecutionTime,
      parallelResult,
      parallelExecutionTime,
      executionTime,
    });
  });
});

app.post("/calculate", (req, res) => {
  const startTime = new Date().getTime();
  const { numberToCheck } = req.body;

  // Szekvenciális keresés a leggyakoribb elem megtalálására
  const sequentialSearch = (array, numberToCheck) => {
    let count = 0;
    array.forEach((item) => {
      if (item === numberToCheck) {
        count++;
      }
    });
    return count;
  };

  // Párhuzamos keresés a leggyakoribb elem megtalálására
  const parallelSearch = (array, numberToCheck) => {
    return new Promise((resolve) => {
      let count = 0;
      array.forEach((item) => {
        if (item === numberToCheck) {
          count++;
        }
      });
      resolve(count);
    });
  };

  // Szekvenciális keresés és ideje
  const sequentialStartTime = new Date().getTime();
  const sequentialCount = sequentialSearch(testData, numberToCheck);
  const sequentialEndTime = new Date().getTime();
  const sequentialExecutionTime = sequentialEndTime - sequentialStartTime;

  // Párhuzamos keresés és ideje
  const parallelStartTime = new Date().getTime();
  const parallelCountPromise = parallelSearch(testData, numberToCheck);
  const parallelEndTime = new Date().getTime();
  const parallelExecutionTime = parallelEndTime - parallelStartTime;

  parallelCountPromise.then((parallelCount) => {
    const endTime = new Date().getTime();
    const executionTime = endTime - startTime;

    res.json({
      sequentialResult: {
        number: numberToCheck,
        frequency: sequentialCount,
      },
      sequentialExecutionTime,
      parallelResult: {
        number: numberToCheck,
        frequency: parallelCount,
      },
      parallelExecutionTime,
      executionTime,
    });
  });
});

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
