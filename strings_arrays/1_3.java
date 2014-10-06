class e1_3 {
  
  public static void main(String[] args) {
    
  }
  
  static boolean isPermutation(String a, String b) {
    if (a == null || b == null)
      return false;
    
    if (a.length() != b.length())
      return false;
    
    return true;
  }
  
}