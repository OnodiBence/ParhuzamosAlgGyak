import React, { useState } from "react";
import axios from "axios";
import "./App.css";

function App() {
  const [result, setResult] = useState(null);
  const [loading, setLoading] = useState(false);
  const [waiting, setWaiting] = useState(false);

  const handleClick = async () => {
    setLoading(true);
    setWaiting(true);
    try {
      const response = await axios.post("http://localhost:5000/calculate");
      setResult(response.data);
      setLoading(false);
      setWaiting(false);
    } catch (error) {
      console.error("Error fetching data:", error);
      setLoading(false);
      setWaiting(false);
    }
  };

  return (
    <div className="container">
      <h1>Most common element occurrence with React and NodeJS</h1>
      <button onClick={handleClick} disabled={loading}>
        Calculate
      </button>
      {loading && <p className="loading">Loading...</p>}
      {waiting && <p className="loading">Waiting for server response...</p>}
      {result && (
        <div className="results">
          {/* <p>Generated Array: {result.testData.join(", ")}</p>   */}
          <p>
            Sequential Result: {result.sequentialResult.number} (Frequency:{" "}
            {result.sequentialResult.frequency})
          </p>
          <p>Sequential Execution Time: {result.sequentialExecutionTime} ms</p>
          <p>
            Parallel Result: {result.parallelResult.number} (Frequency:{" "}
            {result.parallelResult.frequency})
          </p>
          <p>Parallel Execution Time: {result.parallelExecutionTime} ms</p>
          <p>Total Execution Time: {result.executionTime} ms</p>
        </div>
      )}
    </div>
  );
}

export default App;
