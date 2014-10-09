package dk.kunin.generic;

/**
 * Created by 7times6 on 10.10.14.
 */
public class Node<T> {

    public T value;
    public Node<T> next;

    public Node(T value, Node<T> next) {
        this.value = value;
        this.next  = next;
    }

    public Node(T value) {
        this(value, null);
    }
}
