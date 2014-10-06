class e1_4 {
  
  public static void main(String[] args) {
    String[] testSet = {
      null, 
      "", 
      " ", 
      "The FB", 
      "  ", 
      " The Best Thing "
    };
    
    String[] expectedSet = {
      null, 
      "", 
      "%20", 
      "The%20FB", 
      "%20%20", 
      "%20The%20Best%20Thing%20"
    };
    
    for (int i = 0; i < testSet.length; ++i) {
      testEq(encodeSpaces(testSet[i]), expectedSet[i]);
    }
  }
  
  static void testEq(Object a, Object b) {
    boolean passed = false;
    
    if (a != null) {
      passed = a.equals(b);
    } else if (b != null) {
      passed = b.equals(a);
    } else {
      passed = a == b;
    }
    
    if (!passed) 
    {
      throw new RuntimeException(String.format("%s no equals %s", a, b));
    }
    else 
      System.out.println("Passed");
  }
  
  static String encodeSpaces(String input) {
    if (input == null || input.isEmpty())
      return input;
    
    int len = input.length();
    int new_len = 0;
    char[] new_chars = new char[3*len];
    
    for (int i = 0; i < len; ++i) {
      char c = input.charAt(i);
      if (c == ' ') {
        new_chars[new_len++] = '%';
        new_chars[new_len++] = '2';
        new_chars[new_len++] = '0';
      } else {
        new_chars[new_len++] = c;
      }
    }
    
    return new String(new_chars, 0, new_len);
  }
  
}