package dk.kunin;

/**
 * Created by 7times6 on 06.10.14.
 */
public class Stack {

    Node top;

    boolean isEmpty() {
        return top == null;
    }

    void push(int value) {
        Node n = new Node(value);
        n.next = top;
        top = n;
    }

    Node pop() {
        if (top != null) {
            Node tmp = top;
            top = top.next;
            return tmp;
        } else {
            return null;
        }
    }

    Node peek() {
        return top;
    }
}
