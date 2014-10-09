package dk.kunin.generic

import org.junit.Test

/**
 * Created by 7times6 on 06.10.14.
 */
import static org.junit.Assert.assertEquals
import static org.junit.Assert.assertTrue

class StackTest {

    @Test
    void testStack() {
        Stack<Integer> s = new Stack();
        10.times {
            s.push(it)
        }

        9.downto(0) {
            assertEquals(it, s.pop())
        }

        assertTrue s.isEmpty()
    }

    @Test
    void emptyTest() {
        Stack s = new Stack();
        assertTrue s.isEmpty()
    }

    @Test
    void peekTest() {
        Stack<Integer> s = new Stack();
        s.push(1);
        s.push(2);

        assertEquals(2, s.peek())
        assertEquals(2, s.peek())
        assertEquals(2, s.peek())


        assertEquals(2, s.pop())

        assertEquals(1, s.peek())
        assertEquals(1, s.peek())
        assertEquals(1, s.peek())


        assertEquals(1, s.pop())

        assertTrue(s.isEmpty())
    }


}
