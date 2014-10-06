package dk.kunin
import org.junit.Test
import static org.junit.Assert.*
/**
 * Created by 7times6 on 06.10.14.
 */
class NStackTest {

    @Test
    void testCreateValid() {
        def numStacks = 10
        NStack<Integer> s = new NStack<>(numStacks)

        10.times {
            assertTrue s.isEmpty(it)
        }
    }

    @Test
    void testPushPop() {

        def numStack = 5
        def maxVal = 5

        NStack<Integer> s = new NStack<>(numStack)

        numStack.times { stack ->
            maxVal.times { value ->
                s.push(value, stack)
            }
        }

        numStack.times { stack ->
            maxVal.times { value ->
                assertEquals(maxVal - value - 1, s.pop(stack))
            }
        }

        numStack.times {
            assertTrue s.isEmpty(it)
        }
    }

}
