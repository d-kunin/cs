package dk.kunin.generic;

/**
 * Created by 7times6 on 10.10.14.
 */
public class Stack<T> {

    Node<T> first;

    public boolean isEmpty() {
        return first == null;
    }

    public void push(T value) {
        Node<T> n = new Node<T>(value, first);
        first = n;
    }

    public T pop() {
        if (isEmpty()) {
            return null;
        } else {
            T value = first.value;
            first = first.next;
            return value;
        }
    }

    public T peek() {
        if (isEmpty()) {
            return null;
        } else {
            return first.value;
        }
    }
}
