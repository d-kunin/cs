package dk.kunin;

public class Main {

    public static void main(String[] args) {
	    SingleLinkedList list = new SingleLinkedList();
        list.append(1);
        list.printList();

        list.append(2);
        list.append(3);
        list.append(4);
        list.printList();

        list.delete(0);
        list.printList();

        list.delete(1);
        list.printList();

        list.delete(3);
        list.printList();

        list.delete(4);
        list.printList();

        SingleLinkedList rList = new SingleLinkedList();

        rList.reverse();
        rList.printList();

        rList.append(1);
        rList.reverse();
        rList.printList();

        rList.append(2);
        rList.reverse();
        rList.printList();

        rList.reverse();
        rList.printList();

        rList.append(3)
             .append(4);

        rList.reverse();
        rList.printList();

        SingleLinkedList dupeList = new SingleLinkedList();
        dupeList.append(1)
                .append(2)
                .append(1)
                .append(2)
                .append(3)
                .append(1)
                .append(3)
                .append(3)
                .append(3);
        dupeList.printList();

        dupeList.dedupe();
        dupeList.printList();

        SingleLinkedList dupeQuadList = new SingleLinkedList();
        dupeQuadList.append(1)
                .append(2)
                .append(1)
                .append(2)
                .append(3)
                .append(1)
                .append(3)
                .append(3)
                .append(3);
        dupeQuadList.printList();

        dupeQuadList.dedupeLowMemory();
        dupeQuadList.printList();

        System.out.println("KTH iterative");
        SingleLinkedList kth = new SingleLinkedList();
        kth.append(4)
            .append(3)
            .append(2)
            .append(1)
            .append(0);

        SingleLinkedList empty = new SingleLinkedList();
        SingleLinkedList singleItem = new SingleLinkedList();
        singleItem.append(0);

        for (int i = 0; i < 6; ++i) {
            System.out.println(kth.kthFromEnd(i));
        }

        System.out.println(empty.kthFromEnd(0));
        System.out.println(empty.kthFromEnd(1));

        System.out.println(singleItem.kthFromEnd(0));
        System.out.println(singleItem.kthFromEnd(1));

        System.out.println("KTH recursive");
        for (int i = 0; i < 6; ++i) {
            System.out.println(kth.kthFromEndRecur(i));
        }

        System.out.println(empty.kthFromEndRecur(0));
        System.out.println(empty.kthFromEndRecur(1));

        System.out.println(singleItem.kthFromEndRecur(0));
        System.out.println(singleItem.kthFromEndRecur(1));

        System.out.println("Remove node");

        SingleLinkedList cutList = new SingleLinkedList();
        Node node1 = cutList.append(0).append(1);
        Node node3 = cutList.append(2).append(3);
        cutList.append(4);
        cutList.printList();
        cutList.remove(node3);
        cutList.remove(node1);
        cutList.printList();

        System.out.println("Split on x");
        SingleLinkedList splitme = SingleLinkedList.from(3,4,1,2,5,6,0);
        splitme.splitOn(3);
        splitme.printList();
    }
}
