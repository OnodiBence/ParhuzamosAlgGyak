const express = require("express");
const cors = require("cors");
const app = express();
const PORT = 5000;

app.use(cors());
app.use(express.json());

app.post("/calculate", (req, res) => {
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

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
