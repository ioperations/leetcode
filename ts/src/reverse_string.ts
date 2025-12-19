
export default function reverseString(s: string): string {
    const len: number = s.length;
    if (len === 0) {
        return '';
    }

    return s[len - 1] + reverseString(s.substring(0, len - 1));
}
