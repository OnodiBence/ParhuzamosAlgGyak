import React, { useState } from "react";
import axios from "axios";
import "./App.css";

function App() {
  const [results, setResults] = useState([]);
  const [loading, setLoading] = useState(false);
  const [waiting, setWaiting] = useState(false);

  const handleClick = async () => {
    setLoading(true);
    setWaiting(true);
    try {
      const randomNumber = Math.floor(Math.random() * 10) + 1;
      const response = await axios.post("http://localhost:5000/calculate", {
        numberToCheck: randomNumber,
      });
      setResults((prevResults) => [
        ...prevResults,
        { ...response.data, randomNumber },
      ]);
      setLoading(false);
      setWaiting(false);
    } catch (error) {
      console.error("Error fetching data:", error);
      setLoading(false);
      setWaiting(false);
    }
  };

  const generateArray = (length) => {
    return Array.from({ length }, () => Math.floor(Math.random() * 10) + 1);
  };

  return (
    <div className="container">
      <h1>Most common element occurrence with React and NodeJS</h1>
      <button onClick={handleClick} disabled={loading}>
        Calculate
      </button>
      {loading && <p className="loading">Loading...</p>}
      {waiting && <p className="loading">Waiting for server response...</p>}
      {results.length > 0 && (
        <table>
          <thead>
            <tr>
              <th>Random Number</th>
              <th>Sequential Result</th>
              <th>Sequential Frequency</th>
              <th>Sequential Execution Time (ms)</th>
              <th>Parallel Result</th>
              <th>Parallel Frequency</th>
              <th>Parallel Execution Time (ms)</th>
              <th>Total Execution Time (ms)</th>
            </tr>
          </thead>
          <tbody>
            {results.map((res, index) => (
              <tr key={index}>
                <td>{res.randomNumber}</td>
                <td>{res.sequentialResult.number}</td>
                <td>{res.sequentialResult.frequency}</td>
                <td>{res.sequentialExecutionTime}</td>
                <td>{res.parallelResult.number}</td>
                <td>{res.parallelResult.frequency}</td>
                <td>{res.parallelExecutionTime}</td>
                <td>{res.executionTime}</td>
              </tr>
            ))}
          </tbody>
        </table>
      )}
    </div>
  );
}

export default App;
