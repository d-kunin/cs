package dk.kunin;

/**
 * Created by 7times6 on 06.10.14.
 */
public class NStack<T> {

    private T[] data;
    private int[] last;

    private final int numStacks;
    private int perStackCapacity = 10;

    NStack(int numStacks) {
        if (numStacks < 1) {
            throw new IllegalArgumentException("Number of stack must be positve: " + numStacks);
        }

        this.numStacks = numStacks;
        last = new int[numStacks];
        data = (T[]) new Object[numStacks * perStackCapacity];
        for (int i = 0; i < numStacks; ++i) {
            last[i] = i - numStacks;
        }
    }

    public void push(T value, int stack) {
        checkStack(stack);
        last[stack] += numStacks;
        resize(); // grow up?
        data[last[stack]] = value;
    }

    public T pop(int stack) {
        checkStack(stack);
        if (isEmpty(stack)) {
            return null;
        }
        int pos = last[stack];
        T tmp = data[pos];
        data[pos] = null;
        last[stack] -= numStacks;
        resize(); // grow down?
        return tmp;
    }

    public T peek(int stack) {
        checkStack(stack);
        if (isEmpty(stack)) {
            return null;
        }
        return data[last[stack]];
    }

    private void resize() {
        // currently does nothing
        // I love to do nothing
    }

    public boolean isEmpty(int stack) {
        checkStack(stack);
        return last[stack] < 0;
    }

    private void checkStack(int stack) {
        if (stack < 0 || stack >= numStacks) {
            throw new IllegalArgumentException(String.format("Must be between 0 and %d, actual %d", numStacks, stack));
        }
    }
}
