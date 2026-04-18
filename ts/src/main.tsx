import {
  createCliRenderer,
  SyntaxStyle,
  RGBA,
  parseColor,
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
  const [textX, setText] = useState("");
  const [markdownContent, setMarkdownContent] = useState("");
  const [displaySystemMonitor, setDisplay] = useState(true);
  const [i, setI] = useState(0);

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
    keyword: { fg: parseColor("#FF7B72"), bold: true },
    string: { fg: parseColor("#A5D6FF") },
    comment: { fg: parseColor("#8B949E"), italic: true },
    number: { fg: parseColor("#79C0FF") },
    function: { fg: parseColor("#D2A8FF") },
    type: { fg: parseColor("#FFA657") },
    operator: { fg: parseColor("#FF7B72") },
    variable: { fg: parseColor("#E6EDF3") },
    property: { fg: parseColor("#79C0FF") },
    "punctuation.bracket": { fg: parseColor("#F0F6FC") },
    "punctuation.delimiter": { fg: parseColor("#C9D1D9") },
    "markup.heading": { fg: parseColor("#58A6FF"), bold: true },
    "markup.heading.1": {
      fg: parseColor("#00FF88"),
      bold: true,
      underline: true,
    },
    "markup.heading.2": { fg: parseColor("#00D7FF"), bold: true },
    "markup.heading.3": { fg: parseColor("#FF69B4") },
    "markup.bold": { fg: parseColor("#F0F6FC"), bold: true },
    "markup.strong": { fg: parseColor("#F0F6FC"), bold: true },
    "markup.italic": { fg: parseColor("#F0F6FC"), italic: true },
    "markup.list": { fg: parseColor("#FF7B72") },
    "markup.quote": { fg: parseColor("#8B949E"), italic: true },
    "markup.raw": { fg: parseColor("#A5D6FF"), bg: parseColor("#161B22") },
    "markup.raw.block": {
      fg: parseColor("#A5D6FF"),
      bg: parseColor("#161B22"),
    },
    "markup.raw.inline": {
      fg: parseColor("#A5D6FF"),
      bg: parseColor("#161B22"),
    },
    "markup.link": { fg: parseColor("#58A6FF"), underline: true },
    "markup.link.label": { fg: parseColor("#A5D6FF"), underline: true },
    "markup.link.url": { fg: parseColor("#58A6FF"), underline: true },
    label: { fg: parseColor("#7EE787") },
    conceal: { fg: parseColor("#6E7681") },
    "punctuation.special": { fg: parseColor("#8B949E") },
    default: { fg: parseColor("#E6EDF3") },
  });

  const spinnerDef = useMemo(() => {
    const color = RGBA.fromHex("#f8f090"); // slate blue
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
        onComplete: () => {
          setInterval(() => {
            setDisplay(false);
          }, 2000);
        },
      },
      0,
    );
  }, []);

  useEffect(() => {
    var interval = setInterval(() => {
      var content =
        `# Markdown Stream Test

~` +
        textX +
        `~

- hello world
- test
> **italic cubic**
## cpp + rust Solution for leetcode online judge

#### cpp dependency

- gtest and google-benchmark
  - and every solution should contain with at least all leetcode test case
  - maybe contain benchmarks for my implementation and others'

#### rust dependency

- rand
- tokio together with syn quote ...

![img](./flamegraph.svg)

- recent learning
- ![sequence diagram](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/ioperations/leetcode/refs/heads/master/LEARN.iuml) 
`;
      var t = content.length;
      var index = i % t;
      content = content.substring(0, index);
      setMarkdownContent(content);

      setI(i + 1);
    }, 100);
    return () => clearInterval(interval);
  }, [textX, i]);

  const statsMap = [
    { name: "CPU", key: "cpu", color: "#6a5acd" },
    { name: "Memory", key: "memory", color: "#4682b4" },
    { name: "Network", key: "network", color: "#20b2aa" },
    { name: "Disk", key: "disk", color: "#daa520" },
  ];

  return (
    <>
      <box
        paddingLeft={2}
        style={{
          marginTop: 1,
        }}
        border={["left"]}
        borderStyle="heavy"
        borderColor="purple"
      >
        <input placeholder="type here..." onInput={setText} focused={true} />
      </box>
      <scrollbox
        width={`${100}%`}
        height={`${50}%`}
        border
        borderStyle="single"
      >
        <markdown
          streaming={true}
          content={markdownContent}
          syntaxStyle={Style}
        />
      </scrollbox>

      {displaySystemMonitor && (
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
                <text
                  attributes={TextAttributes.DIM | TextAttributes.UNDERLINE}
                >
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
      )}
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
