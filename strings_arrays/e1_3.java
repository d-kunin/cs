class e1_3 {
  
  public static void main(String[] args) {
    String[] as = {null, "", "ab", "asdf", "qazedc"};
    String[] bs = {null, " ", "ba", "fdsa", "cdewsx"};
    boolean[] expectetions = {false, false, true, true, false};
    
    for (int i = 0; i < as.length; ++i){
      test(expectetions[i], isPermutation(as[i], bs[i]));
    }
  }
  
  static void test(boolean expected, boolean actual) {
    if (expected != actual)
      throw new RuntimeException();
    else 
      System.out.println("Passed");
  }
  
  static boolean isPermutation(String a, String b) {
    if (a == null || b == null)
      return false;
    
    if (a.length() != b.length())
      return false;
    
    int[] counts = new int[256];
    
    for (int i = 0; i < a.length(); ++i) {
      char c = a.charAt(i);
      counts[c]++;
    }
    
    for (int i = 0; i < b.length(); ++i) {
      char c = b.charAt(i);
      counts[c]--;
      if (counts[c] < 0)
        return false;
    }
    
    return true;
  }
  
}