import {
  createCliRenderer,
  SyntaxStyle,
  RGBA,
  TextAttributes,
} from "@opentui/core";
import { createRoot, useTimeline } from "@opentui/react";
import { useEffect, useMemo, useState } from "react";
import { createColors, createFrames } from "./spinner";
import "opentui-spinner/react";

type Stats = {
  cpu: number;
  memory: number;
  network: number;
  disk: number;
};

function App() {
  const [width, setWidth] = useState(0);
  const [text, setText] = useState("");

  const [stats, setAnimatedStats] = useState<Stats>({
    cpu: 0,
    memory: 0,
    network: 0,
    disk: 0,
  });

  const timeline = useTimeline({
    duration: 3000,
    loop: false,
  });

  const Style = SyntaxStyle.fromStyles({
    keyword: { fg: RGBA.fromHex("#ff6b6b"), bold: true }, // red, bold
    string: { fg: RGBA.fromHex("#51cf66") }, // green
    comment: { fg: RGBA.fromHex("#868e96"), italic: true }, // gray, italic
    number: { fg: RGBA.fromHex("#ffd43b") }, // yellow
    default: { fg: RGBA.fromHex("#ffffff") }, // white
  });

  const spinnerDef = useMemo(() => {
    const color = RGBA.fromHex("#6a5acd"); // slate blue
    return {
      frames: createFrames({
        color,
        style: "blocks",
        inactiveFactor: 0.6,
        // enableFading: false,
        minAlpha: 0.3,
      }),
      color: createColors({
        color,
        style: "blocks",
        inactiveFactor: 0.6,
        // enableFading: false,
        minAlpha: 0.3,
      }),
    };
  }, []);

  useEffect(() => {
    timeline.add(
      stats,
      {
        cpu: 85,
        memory: 70,
        network: 95,
        disk: 60,
        duration: 3000,
        ease: "linear",
        onUpdate: (values) => {
          setAnimatedStats({ ...values.targets[0] });
        },
      },
      0,
    );
  }, []);

  const statsMap = [
    { name: "CPU", key: "cpu", color: "#6a5acd" },
    { name: "Memory", key: "memory", color: "#4682b4" },
    { name: "Network", key: "network", color: "#20b2aa" },
    { name: "Disk", key: "disk", color: "#daa520" },
  ];

  return (
    <>
      <box />
      <box
        style={{
          marginTop: 1,
        }}
        border={true}
        borderStyle="single"
        borderColor="#4a4a4a"
      >
        <input placeholder="type here..." onInput={setText} focused={true} />
      </box>
      <text visible={!!text}>{text}</text>
      <markdown content={text} syntaxStyle={Style} />
      <box
        title="System Monitor"
        style={{
          margin: 1,
          padding: 1,
          border: true,
          marginLeft: 2,
          marginRight: 2,
          borderStyle: "single",
          borderColor: "#4a4a4a",
        }}
      >
        {statsMap.map((stat) => (
          <box key={stat.key}>
            <box flexDirection="row" justifyContent="space-between">
              <text>{stat.name}</text>
              <text attributes={TextAttributes.DIM | TextAttributes.UNDERLINE}>
                {Math.round(stats[stat.key as keyof Stats])}%
              </text>
            </box>
            <box style={{ backgroundColor: "#333333" }}>
              <box
                style={{
                  width: `${stats[stat.key as keyof Stats]}%`,
                  height: 1,
                  backgroundColor: stat.color,
                }}
              />
            </box>
          </box>
        ))}
      </box>
      <spinner
        color={spinnerDef.color}
        frames={spinnerDef.frames}
        interval={40}
      />
    </>
  );
}

if (import.meta.main) {
  const renderer = await createCliRenderer();
  createRoot(renderer).render(<App />);
}
