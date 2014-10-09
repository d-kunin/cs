package dk.kunin

import org.junit.Test

import static org.junit.Assert.assertEquals
import static org.junit.Assert.assertTrue;

/**
 * Created by 7times6 on 06.10.14.
 */
class TwoStackQueueTest {

    @Test
    void testEmpty() {
        TwoStackQueue q = new TwoStackQueue();
        assertTrue q.isEmpty()
    }

    @Test
    void testAddRemove() {
        TwoStackQueue q = new TwoStackQueue();
        q.enqueue(1)
        assertEquals(1, q.dequeue())
        assertTrue q.isEmpty()
    }

    @Test
    void testQueue() {
        TwoStackQueue q = new TwoStackQueue();
        10.times {
            q.enqueue(it)
        }

        10.times {
            assertEquals(it, q.dequeue())
        }

        assertTrue q.isEmpty()
    }

}
