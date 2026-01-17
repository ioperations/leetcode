import { describe, expect, test } from "@jest/globals";
import reverseString from "../src/reverse_string";

describe("reverseString module", () => {
  test("reverses a string", () => {
    expect(reverseString("hello")).toBe("olleh");
    expect(reverseString("world")).toBe("dlrow");
  });
});
