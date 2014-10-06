package dk.kunin;

/**
 * Created by 7times6 on 04.10.14.
 */
public class PrintVisitor implements Node.NodeVisitor{

    @Override
    public void visit(Node n) {
        System.out.printf("[%2d]", n.data);
    }
}
