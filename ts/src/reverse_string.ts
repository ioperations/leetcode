
export default function reverseString(s: string): string {
    let res = '';
    if (s.length === 0) {
        return res;
    }

    return s[s.length - 1] + reverseString(s.substring(0, s.length - 1));
}
