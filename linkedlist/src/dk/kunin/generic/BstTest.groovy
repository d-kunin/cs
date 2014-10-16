package dk.kunin.generic

import org.junit.Test

import static org.junit.Assert.*

/**
 * Created by 7times6 on 06.10.14.
 */
class BstTest {

    @Test
    void testEmpty() {
        BST<Integer> bst = new BST<>()
        assertTrue bst.isEmpty()
        assertNull(bst.find(1))
    }

    @Test
    void testAdd() {
        BST<Integer> bst = new BST<>()

        assertEquals(1, bst.add(1).key)
        assertEquals(2, bst.add(2).key)

        assertNotNull bst.add(3)
        assertNotNull bst.add(0)
        assertNotNull bst.add(-42)
    }

    @Test
    void testFind() {
        BST<Integer> bst = new BST<>()

        assertNull(bst.find(0))
        bst.add(42)
        assertEquals(42, bst.find(42).key)

        def keys = [1, 2, 3, -1, -2]
        def notkeys = [11, 0, 15, 777]

        keys.each {
            bst.add(it)
        }

        notkeys.each {
            assertNull(bst.find(it))
        }

        keys.each {
            assertEquals(it, bst.find(it).key)
        }

    }

    @Test
    void testWalks() {

        def empty = new BST<Integer>()
        def tree = new BST<Integer>();
        def keys = [1, 2, 3, -1, -2, 99, -99, -10, 0]
        keys.each {
            tree.add(it)
        }
        def printer = { n -> printf("{%d} ", n) }

        def trees = [empty, tree];

        trees.each { t ->
            println "pre-order:"
            t.foreach(printer, BST.WalkType.PRE_ORDER)

            println "\nin-order:"
            t.foreach(printer, BST.WalkType.IN_ORDER)

            println "\npost-order:"
            t.foreach(printer, BST.WalkType.POST_ORDER)

            println "\nBFS:"
            t.foreach(printer, BST.WalkType.BSF)

            t.checkTree()
        }
    }

    @Test
    void testHeight() {
        def empty = new BST()
        assertEquals(0, empty.height())

        def onlyRoot = new BST<Integer>();
        onlyRoot.add(2)
        assertEquals(1, onlyRoot.height())

        def hasChild = new BST<Integer>()
        hasChild.add(0)
        hasChild.add(-1)
        assertEquals(2, hasChild.height())
        hasChild.add(1)
        assertEquals(2, hasChild.height())
        hasChild.add(3)
        assertEquals(3, hasChild.height())
        hasChild.add(4)
        assertEquals(4, hasChild.height())
        hasChild.add(-2)
        assertEquals(4, hasChild.height())

        System.out.println();
        hasChild.foreach({
            System.out.printf(" {%2d} ", it)
        }, BST.WalkType.BSF)
    }

    @Test
    void testBalanced() {
        def tree = new BST<Integer>()
        assertTrue(tree.isBalanced())

        tree.add(0)
        assertTrue(tree.isBalanced())

        tree.add(1)
        assertTrue(tree.isBalanced())

        tree.add(-1)
        assertTrue(tree.isBalanced())

        tree.add(-2)
        assertTrue(tree.isBalanced())

        tree.add(-3)
        assertFalse(tree.isBalanced())

        tree = new BST<Integer>()
        10.times {
            tree.add(it)
        }
        assertFalse(tree.isBalanced())
    }


    @Test
    void testCreateBalanced() {
        def empty = BST.createBalanced([]);
        assertTrue(empty.isBalanced())

        def oneNodeTree = BST.createBalanced([1])
        assertTrue(oneNodeTree.isBalanced())

        def r = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        def tree = BST.createBalanced(r)
        assertTrue(tree.isBalanced())
        assertEquals(4, tree.height())

        // 'couple' of random tests
        def rand = new Random()
        1000.times {
            def keys = []
            // add
            rand.nextInt(100).times {
                keys.add(it)
            }
            // make some gaps
            rand.nextInt(10).times {
                if (!keys.empty) {
                    def index = rand.nextInt(keys.size())
                    keys.remove((int)index)
                }
            }
            // create tree
            tree  = BST.createBalanced(keys)
            // it must be balanced
            assertTrue(keys.toString(), tree.isBalanced())
        }

    }

}
