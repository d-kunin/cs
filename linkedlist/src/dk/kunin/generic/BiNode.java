package dk.kunin.generic;

import org.testng.collections.Lists;

import java.util.List;
import java.util.stream.Collectors;

/**
 * Created by 7times6 on 10.10.14.
 */
public class BiNode<T> {

    T key;

    public BiNode<T> left;
    public BiNode<T> right;

    public BiNode(T key, BiNode<T> left, BiNode<T> right) {
        this.key = key;
        this.left = left;
        this.right = right;
    }

    public List<BiNode<T>> children() {
        return Lists.newArrayList(left, right)
                .stream()
                .filter( n -> n != null)
                .collect(Collectors.toList());
    }
}
