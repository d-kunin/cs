package dk.kunin;

import java.util.HashSet;
import java.util.Set;

/**
 * Created by 7times6 on 04.10.14.
 */
public class SingleLinkedList {

    Node head;

    boolean isEmpty() {
        return head != null;
    }

    public static SingleLinkedList from(int ... values) {
        SingleLinkedList list = new SingleLinkedList();
        for (int value : values) {
            list.append(value);
        }
        return list;
    }

    Node append(int data) {
        Node node = new Node(data);

        if (head == null) {
            head = node;
        } else {
            Node n = head;
            while (n.next != null) {
                n = n.next;
            }
            n.next = node;
        }

        return node;
    }

    boolean delete(int data) {
        if (head == null) {
            return false;
        }

        if (head.data == data) {
            head = head.next;
            return true;
        }

        Node prev = head;
        Node n    = head.next;
        while (n != null && n.data != data) {
            prev = n;
            n = n.next;
        }

        // found node
        if (n != null) {
            prev.next = n.next;
            return true;
        } else {
            return false;
        }
    }

    void foreach(Node.NodeVisitor visitor) {
        Node n = head;
        while (n != null) {
            visitor.visit(n);
            n = n.next;
        }
    }

    void printList() {
        System.out.print("List:{");
        if (head != null) {
            foreach(new PrintVisitor());
        } else {
            System.out.print("null");
        }
        System.out.println("}");
    }

    void reverse() {
        Node p = null;
        Node n = head;

        while (n != null) {
            Node tmp = n.next;
            n.next = p;
            p = n;
            n = tmp;
        }
        head = p;
    }

    void dedupe() {

       Node prev = null;
       Node n    = head;
       Set<Integer> index = new HashSet<>();

       while (n != null) {
           if (index.contains(n.data)) {
               prev.next = n.next;
               n = prev.next;
           } else {
               index.add(n.data);
               prev = n;
               n = n.next;
           }
       }
    }

    void dedupeLowMemory() {
        Node vnode = head;
        while (vnode != null) {
            int value = vnode.data;
            Node p = vnode;
            Node n = vnode.next;
            while (n != null) {
                if (n.data == value) {
                    p.next = n.next;
                    n = p.next;
                } else {
                    p = n;
                    n = n.next;
                }
            }
            vnode = vnode.next;
        }
    }

    Node kthFromEnd(int k) {
        if (k < 0) {
            return null;
        }

        Node kth = head;
        Node runner = head;
        int countdown = k;
        while (runner != null) {
            if (countdown < 0) {
                kth = kth.next;
            } else {
               countdown--;
            }
            runner = runner.next;
        }
        return countdown < 0 ? kth : null;
    }

    Node kthFromEndRecur(int k) {
        return _kthFromEndRecur(head, head, k);
    }

    private Node _kthFromEndRecur(Node cur, Node mem, int k) {
        if (cur == null)
            return k < 0 ? mem : null;

        if (k < 0) {
            mem = mem.next;
        }
        return _kthFromEndRecur(cur.next, mem, k - 1);
    }

    boolean remove(Node n) {
        if (n == null || n.next == null) {
            return false;
        }

        n.data = n.next.data;
        n.next = n.next.next;
        return true;
    }

    void splitOn(int x) {

        Node lHead = null,
             lEnd = null,
             geHead = null,
             geEnd = null;

        Node n = head;
        while (n != null) {
            int value = n.data;
            Node newNode = new Node(value);
            if (value < x) {
                if (lHead == null) {
                    lHead = newNode;
                    lEnd = lHead;
                } else {
                    lEnd.next = newNode;
                    lEnd = lEnd.next;
                }
            } else {
                if (geHead == null) {
                    geHead = newNode;
                    geEnd = geHead;
                } else {
                    geEnd.next = newNode;
                    geEnd = geEnd.next;
                }
            }

            n = n.next;
        }

        // concat lists
        if (lHead == null) {
            head = geHead;
        } else {
            lEnd.next = geHead;
            head = lHead;
        }
    }
}
