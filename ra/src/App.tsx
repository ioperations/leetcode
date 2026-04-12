import React from "react";
import logo from "./logo.svg";
import "./App.css";
import { LineChart, Line, XAxis, Tooltip, CartesianGrid, YAxis } from "recharts";

function App() {
  const data = [
    { time: "2025 01", uv: 1600, pv: 5400, amt: 5400 },
    { time: "2025 02", uv: 3900, pv: 4567, amt: 5400 },
    { time: "2025 03", uv: 1700, pv: 1398, amt: 5400 },
    { time: "2025 04", uv: 8978, pv: 3908, amt: 5400 },
    { time: "2025 05", uv: 1589, pv: 4800, amt: 5400 },
    { time: "2025 06", uv: 1239, pv: 3800, amt: 5400 },
    { time: "2025 07", uv: 3349, pv: 4300, amt: 5400 },
  ];

  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <div className="charts">
          <LineChart width={1600} height={300} data={data}>
            <XAxis dataKey="time" padding={{left:20, right: 30}}/>
            <YAxis padding={{ top: 10, bottom: 10 }} />
            <Tooltip />
            <CartesianGrid  />
            <Line type="monotone" dataKey="uv" stroke="#ff7300" />
            <Line type="monotone" dataKey="pv" stroke="#387908" />
            <Line type="monotone" dataKey="amt" stroke="#880908" />
          </LineChart>
        </div>
      </header>
    </div>
  );
}

export default App;
