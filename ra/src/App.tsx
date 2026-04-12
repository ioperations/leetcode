import React from "react";
import logo from "./logo.svg";
import "./App.css";
import { LineChart, Line, XAxis, CartesianGrid, YAxis } from "recharts";

const App = () =>  {
  const data = [
    {
      name: "A",
      uv: 400,
      pv: 240,
      amt: 2400,
    },
    {
      name: "B",
      uv: 300,
      pv: 456,
      amt: 2400,
    },
    {
      name: "C",
      uv: 300,
      pv: 139,
      amt: 2400,
    },
    {
      name: "D",
      uv: 200,
      pv: 980,
      amt: 2400,
    },
    {
      name: "E",
      uv: 278,
      pv: 390,
      amt: 2400,
    },
    {
      name: "F",
      uv: 189,
      pv: 480,
      amt: 2400,
    },
  ];

  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <LineChart
          style={{
            width: "100%",
            aspectRatio: 2.118,
            maxWidth: 1200,
            margin: "auto",
          }}
          responsive
          data={data}
        >
          <CartesianGrid stroke="var(--color-border-3)" strokeDasharray="5 5" />
          <XAxis dataKey="name" stroke="var(--color-text-3)" />
          <YAxis width="auto" stroke="var(--color-text-3)" />
          <Line
            type="monotone"
            dataKey="uv"
            stroke="var(--color-chart-1)"
            dot={{
              fill: "var(--color-surface-base)",
            }}
            activeDot={{
              stroke: "var(--color-surface-base)",
            }}
          />
          <Line
            type="monotone"
            dataKey="pv"
            stroke="var(--color-chart-2)"
            dot={{
              fill: "var(--color-surface-base)",
            }}
            activeDot={{
              stroke: "var(--color-surface-base)",
            }}
          />
        </LineChart>
      </header>
    </div>
  );
}

export default App;
