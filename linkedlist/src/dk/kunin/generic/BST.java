package dk.kunin.generic;

import com.sun.istack.internal.NotNull;

import java.lang.reflect.Array;
import java.util.*;
import java.util.function.Function;

/**
 * Created by 7times6 on 10.10.14.
 */
public class BST<T extends Comparable> {

    BiNode<T> root;

    BiNode<T> add(T key) {
        BiNode<T> newNode = new BiNode<>(key, null, null);

        if (isEmpty()) {
            root = newNode;
            return root;
        }

        BiNode<T> node = root;
        BiNode<T> parent = null;

        while (node != null) {
            parent = node;
            if (key.compareTo(node.key) < 0) {
                node = node.left;
            } else {
                node = node.right;
            }
        }


        if (key.compareTo(parent.key) < 0) {
            parent.left = newNode;
        } else {
            parent.right = newNode;
        }

        return newNode;
    }

    BiNode<T> find(T key) {
        BiNode<T> node = root;
        while (node != null && !key.equals(node.key)) {
            if (key.compareTo(node.key) < 0) {
                node = node.left;
            } else {
                node = node.right;
            }
        }
        return node;
    }

    boolean isEmpty() {
        return root == null;
    }

    public void foreach(@NotNull Function<T, Void> fun, WalkType walk) {
        walk.walk(root, fun);
    }

    public void dfs(@NotNull Function<T, Void> fun) {
        foreach(fun, WalkType.PRE_ORDER);
    }

    public enum WalkType {
        PRE_ORDER {
            @Override
            public void walk(BiNode node, Function fun) {
                if (node != null) {
                    fun.apply(node.key);
                    walk(node.left, fun);
                    walk(node.right, fun);
                }
            }
        },
        IN_ORDER {
            @Override
            public void walk(BiNode node, Function fun) {
                if (node != null) {
                    walk(node.left, fun);
                    fun.apply(node.key);
                    walk(node.right, fun);
                }
            }
        },
        POST_ORDER {
            @Override
            public void walk(BiNode node, Function fun) {
                if (node != null) {
                    walk(node.left, fun);
                    walk(node.right, fun);
                    fun.apply(node.key);
                }
            }
        },
        BSF {
            @Override
            void walk(BiNode node, Function fun) {
                Queue<BiNode> queue = new LinkedList<>();
                queue.add(node);
                while (!queue.isEmpty() && queue.peek() != null) {
                    BiNode n  = queue.poll();
                    fun.apply(n.key);
                    for (Object o : n.children()) {
                        BiNode child = (BiNode)o;
                        queue.add(child);
                    }
                }
            }
        };

        abstract void walk(BiNode node, Function fun);
    }

    final public void checkTree() {
        new TreeValidator().apply(root);
    }

    final public int height() {
        return new HeightCalc().apply(root);
    }

    final public boolean isBalanced() {
        return _balanced(root);
    }

    final private boolean _balanced(BiNode<T> n) {
        if (n == null)
            return true;

        HeightCalc heightCalc = new HeightCalc();
        int lHeight = heightCalc.apply(n.left);
        int rHeight = heightCalc.apply(n.right);
        if (Math.abs(lHeight - rHeight) > 1) {
            return false;
        }
        if (n.left != null || n.right != null) {
            return _balanced(n.left) && _balanced(n.right);
        }
        return true;
    }

    final class TreeValidator implements Function<BiNode<T>, Void> {
        @Override
        public Void apply(BiNode<T> node) {
            if (node != null) {
                if (node.left != null) {
                    if (node.left.key.compareTo(node.key) >= 0) {
                        throw new IllegalStateException("Left child greater than parent");
                    }
                    apply(node.left);
                }
                if (node.right != null) {
                    if (node.right.key.compareTo(node.key) < 0) {
                        throw new IllegalStateException("Right child less than parent.");
                    }
                    apply(node.right);
                }
            }
            return null;
        }
    }

    final class HeightCalc implements Function<BiNode<T>, Integer> {
        @Override
        public Integer apply(BiNode<T> tNode) {
            return _apply(tNode, 0);
        }

        private Integer _apply(BiNode<T> node, int currentHeight) {
            if (node != null) {
                int lHeight = _apply(node.left, currentHeight + 1);
                int rHeight = _apply(node.right, currentHeight + 1);
                return Math.max(lHeight, rHeight);
            } else {
                return currentHeight;
            }
        }
    }

    public final static <T extends Comparable> BST<T>  createBalanced(List<T> values) {
        BST<T> tree = new BST<>();

        if (values != null) {
            Collections.sort(values);
            addFromMiddle(tree, 0, values.size() - 1, values);
        }

        return tree;
    }

    private final static <T extends Comparable> void addFromMiddle(BST<T> tree, int l, int r, List<T> list) {
            if ( l <= r ) {
                int mid = (r + l) / 2;
                tree.add(list.get(mid));
                addFromMiddle(tree, l, mid - 1, list);
                addFromMiddle(tree, mid + 1, r, list);
            }
    }
}
