package dk.kunin.generic

import org.junit.Test

import static org.junit.Assert.assertEquals
import static org.junit.Assert.assertNull

/**
 * Created by 7times6 on 06.10.14.
 */
import static org.junit.Assert.assertTrue

class ExtremeStackTest {

    @Test
    void testEmpty() {
        ExtremeStack<Integer> minStack = new ExtremeStack<>()
        assertTrue(minStack.isEmpty())
        assertNull(minStack.extreme())
    }

    @Test
    void testMin() {
        ExtremeStack<Integer> minStack = new ExtremeStack<>()

        minStack.push(100)
        assertEquals(100, minStack.extreme())

        minStack.push(1000)
        assertEquals(100, minStack.extreme())

        minStack.push(1)
        assertEquals(1, minStack.extreme())

        minStack.push(11)
        minStack.push(1)
        minStack.push(12) // 12
        assertEquals(1, minStack.extreme())

        minStack.pop() // 1
        assertEquals(1, minStack.extreme())

        minStack.pop() // 11
        assertEquals(1, minStack.extreme())

        minStack.pop() // 1
        assertEquals(1, minStack.extreme())

        minStack.pop() // 1000
        assertEquals(100, minStack.extreme())

        minStack.pop() // 100
        assertEquals(100, minStack.extreme())

        minStack.pop() // null
        assertEquals(null, minStack.extreme())
    }

}
