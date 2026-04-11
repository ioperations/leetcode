import { createCliRenderer } from "@opentui/core";
import { createRoot, useTimeline } from "@opentui/react";
import { useEffect, useState } from "react";

function App() {
  const [width, setWidth] = useState(0);

  const timeline = useTimeline({
    duration: 2000,
    loop: false,
  });

  useEffect(() => {
    timeline.add(
      {
        width,
      },
      {
        width: 50,
        duration: 2000,
        ease: "inBounce",
        onUpdate: (animation) => {
          setWidth(animation.targets[0].width);
        },
      },
    );
  }, []);

  return <box style={{ width, backgroundColor: "#6a5acd" }} />;
}

if (import.meta.main) {
  const renderer = await createCliRenderer();
  createRoot(renderer).render(<App />);
}
