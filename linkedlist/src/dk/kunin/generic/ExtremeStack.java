package dk.kunin.generic;

import com.sun.istack.internal.NotNull;

import java.util.Comparator;

/**
 * Created by 7times6 on 10.10.14.
 */
public class ExtremeStack<T extends Comparable<T>> {

    final Stack<T> extremeStack = new Stack<>();
    final Stack<T> stack        = new Stack<>();

    Comparator<T> comparator = new Comparator<T>() { // just default impl
        @Override
        public int compare(T o1, T o2) {
            return o1.compareTo(o2);
        }
    };

    public ExtremeStack() {}

    public ExtremeStack(@NotNull Comparator<T> comparator) {
        this.comparator = comparator;
    }

    public T extreme() {
        return extremeStack.peek();
    }

    public boolean isEmpty() {
        return stack.isEmpty();
    }

    public void push(T value) {
        stack.push(value);

        if (extremeStack.isEmpty()) {
            extremeStack.push(value);
        } else {
            if (value.compareTo(extreme()) <= 0) {
                extremeStack.push(value);
            }
        }
    }

    public T pop() {
        if (isEmpty()) {
            return null;
        }

        T value = stack.pop();

        if (value.compareTo(extreme()) == 0) {
            extremeStack.pop();
        }

        return value;
    }


}
