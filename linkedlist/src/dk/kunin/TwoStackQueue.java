package dk.kunin;

/**
 * Created by 7times6 on 10.10.14.
 */
public class TwoStackQueue {

    Stack a = new Stack();
    Stack b = new Stack();

    void enqueue(int value) {
        while (!b.isEmpty()) {
            a.push(b.pop().data);
        }
        a.push(value);

        while (!a.isEmpty()) {
            b.push(a.pop().data);
        }
    }

    int dequeue() {
        if (b.isEmpty()) {
            return -1; // no good at all
        } else {
            return b.pop().data;
        }
    }

    public boolean isEmpty() {
        return b.isEmpty();
    }
}
