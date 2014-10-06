package dk.kunin;

/**
 * Created by 7times6 on 06.10.14.
 */
public class Queue {

    Node first;
    Node last;

    boolean isEmpty() {
        return first == null;
    }

    void enqueue(int value) {
        Node n = new Node(value);
        if (isEmpty()) {
            first = n;
            last = first;
        } else {
            last.next = n;
            last = n;
        }
    }

    Node dequeue() {
        if (isEmpty()) {
            return null;
        } else {
            Node tmp = first;
            first = first.next;
            return tmp;
        }
    }

    Node peek() {
        return first;
    }

}
