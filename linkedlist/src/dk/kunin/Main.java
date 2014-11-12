package dk.kunin;

import com.beust.jcommander.internal.Lists;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main {

    /**
     * Implement prepare and isMember such that isMember will return true if the
     * query matches a word in the list passed into prepare.
     *
     * The query string may include any number of "." characters which should match
     * any single character.
     *
     * Examples:
     * c.t matches cat and cot but not coat
     * . matches any single character word such as a or i
     * ... matches any three letter word
     */

    public static class SpellCheck {

    final static char WILD_CARD = '.';
    final WordsTree wordsIndex = new WordsTree();

    static class Node {

        final char value;
        final boolean terminate;
        final Map<Character, Node> children = new HashMap<>();

        Node(char value, boolean terminate) {
            this.value = value;
            this.terminate = terminate;
        }

        Node add(char c, boolean terminate) {
            Node n = children.get(c);
            if (n == null) {
                n = new Node(c, terminate);
                children.put(c, n);
            }
            return n;
        }


        boolean findRec(String postfix) {
                char c = postfix.charAt(0);

                if (c == WILD_CARD) {

                    // handle single '.'
                    if (postfix.length() == 1) {
                        // we just need any terminate-child
                        for (Node child : children.values()) {
                            if (child.terminate) {
                                return true;
                            }
                            return false;
                        }
                    }

                    boolean found = false;
                    for (Node child : children.values()) {
                        if (child.findRec(postfix.substring(1))) {
                            found = true;
                            break;
                        }
                    }
                    return found;


                } else {

                    Node n = children.get(c);
                    if (n == null) {
                        return false;
                    }
                    return postfix.length() == 1
                            ? n.terminate
                            : n.findRec(postfix.substring(1));
                }
        }
    }


        static class WordsTree {
            Node root = new Node((char) 0, false);

            void add(String word) {
                Node n = root;
                for (int i = 0; i < word.length() - 1; ++i) {
                    char c = word.charAt(i);
                    n = n.add(c, false);
                }
                n.add(word.charAt(word.length() - 1), true);
            }

            boolean find(String word) {
                Node n = root;
                return root.findRec(word);
            }
        }

        public void prepare(List<String> words) {
            for (String word : words)
            {
                wordsIndex.add(word);
            }
        }

        public boolean isMember(String query) {
            return wordsIndex.find(query);
        }
    }

    public static void main(String[] args) {
        List<String> dict = Lists.newArrayList(
                "car",
                "cat",
                "count",
                "mate"
        );

        SpellCheck spellCheck = new SpellCheck();
        spellCheck.prepare(dict);

        List<String> tests = Lists.newArrayList(
                "cat",
                "car",
                "count",
                "c...t",
                "ca",
                "...",
                "malina",
                ".",
                "ca.",
                "made",
                "m..e"
        );

        for (String t : tests) {
            System.out.printf("%s : %b\n", t, spellCheck.isMember(t));
        }
    }

    private static void temp() {
        SingleLinkedList list = new SingleLinkedList();
        list.append(1);
        list.printList();

        list.append(2);
        list.append(3);
        list.append(4);
        list.printList();

        list.delete(0);
        list.printList();

        list.delete(1);
        list.printList();

        list.delete(3);
        list.printList();

        list.delete(4);
        list.printList();

        SingleLinkedList rList = new SingleLinkedList();

        rList.reverse();
        rList.printList();

        rList.append(1);
        rList.reverse();
        rList.printList();

        rList.append(2);
        rList.reverse();
        rList.printList();

        rList.reverse();
        rList.printList();

        rList.append(3)
             .append(4);

        rList.reverse();
        rList.printList();

        SingleLinkedList dupeList = new SingleLinkedList();
        dupeList.append(1)
                .append(2)
                .append(1)
                .append(2)
                .append(3)
                .append(1)
                .append(3)
                .append(3)
                .append(3);
        dupeList.printList();

        dupeList.dedupe();
        dupeList.printList();

        SingleLinkedList dupeQuadList = new SingleLinkedList();
        dupeQuadList.append(1)
                .append(2)
                .append(1)
                .append(2)
                .append(3)
                .append(1)
                .append(3)
                .append(3)
                .append(3);
        dupeQuadList.printList();

        dupeQuadList.dedupeLowMemory();
        dupeQuadList.printList();

        System.out.println("KTH iterative");
        SingleLinkedList kth = new SingleLinkedList();
        kth.append(4)
            .append(3)
            .append(2)
            .append(1)
            .append(0);

        SingleLinkedList empty = new SingleLinkedList();
        SingleLinkedList singleItem = new SingleLinkedList();
        singleItem.append(0);

        for (int i = 0; i < 6; ++i) {
            System.out.println(kth.kthFromEnd(i));
        }

        System.out.println(empty.kthFromEnd(0));
        System.out.println(empty.kthFromEnd(1));

        System.out.println(singleItem.kthFromEnd(0));
        System.out.println(singleItem.kthFromEnd(1));

        System.out.println("KTH recursive");
        for (int i = 0; i < 6; ++i) {
            System.out.println(kth.kthFromEndRecur(i));
        }

        System.out.println(empty.kthFromEndRecur(0));
        System.out.println(empty.kthFromEndRecur(1));

        System.out.println(singleItem.kthFromEndRecur(0));
        System.out.println(singleItem.kthFromEndRecur(1));

        System.out.println("Remove node");

        SingleLinkedList cutList = new SingleLinkedList();
        Node node1 = cutList.append(0).append(1);
        Node node3 = cutList.append(2).append(3);
        cutList.append(4);
        cutList.printList();
        cutList.remove(node3);
        cutList.remove(node1);
        cutList.printList();

        System.out.println("Split on x");
        SingleLinkedList splitme = SingleLinkedList.from(3,4,1,2,5,6,0);
        splitme.splitOn(3);
        splitme.printList();
    }
}
