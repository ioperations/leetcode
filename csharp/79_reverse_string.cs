namespace csharp.Tests;

public class ReverseString
{
    public String ReverseStringMethod(String s)
    {
        char[] charArray = s.ToCharArray();
        if (charArray.Length == 0)
        {
            return "";
        }

        return ReverseStringMethod(s.Substring(1)) + (charArray[0]).ToString();
    }

    public String ReverseStringMethodV2(String s)
    {
        char[] sArray = s.ToCharArray();

        for (int i = 0, j = sArray.Length - 1; i < j; i++, j--)
        {
            char temp = sArray[i];
            sArray[i] = sArray[j];
            sArray[j] = temp;
        }

        return new String(sArray);
    }
}

public class ReverseStringTest
{
    [Fact]
    public void BasicTest()
    {
        String input = "hello";
        ReverseString reverser = new ReverseString();
        String result = reverser.ReverseStringMethod(input);
        Assert.Equal("olleh", result);
    }

    [Fact]
    public void BasicTestV2()
    {
        String input = "hello";
        ReverseString reverser = new ReverseString();
        String result = reverser.ReverseStringMethodV2(input);
        Assert.Equal("olleh", result);
    }
}