package dk.kunin;

/**
 * Created by 7times6 on 04.10.14.
 */
public class Node {

    int data;
    Node next;

    public Node(int data) {
        this.data = data;
    }

    void accept(NodeVisitor visitor) {
        visitor.visit(this);
    }

    interface NodeVisitor {
        void visit(Node n);
    }

    Node append(int data) {
        next = new Node(data);
        return next;
    }

    @Override
    public String toString() {
        return "[" + data + "]";
    }
}
