package dk.kunin

import org.junit.Test
import static org.junit.Assert.*;

/**
 * Created by 7times6 on 06.10.14.
 */
class QueueTest  {

    @Test
    void testEmpty() {
        Queue q = new Queue();
        assertTrue q.isEmpty()
    }

    @Test
    void testAddRemove() {
        Queue q = new Queue();
        q.enqueue(1)
        assertEquals(1, q.dequeue().data)
        assertTrue q.isEmpty()
    }

    @Test
    void testQueue() {
        Queue q = new Queue();
        10.times {
            q.enqueue(it)
        }

        10.times {
            assertEquals(it, q.dequeue().data)
        }

        assertTrue q.isEmpty()
    }

}
