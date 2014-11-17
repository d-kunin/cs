package dk.kunin.junk;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;

public class SCCKosaraju {

    public static List<List<Integer>> scc(List<Integer>[] graph) {
        int n = graph.length;
        boolean[] used = new boolean[n];
        List<Integer> order = new ArrayList<>();
        for (int i = n - 1; i >= 0; --i)
            if (!used[i])
                dfs(graph, used, order, i);

        List<Integer>[] reverseGraph = new List[n];
        for (int i = 0; i < n; i++)
            reverseGraph[i] = new ArrayList<>();
        for (int i = 0; i < n; i++)
            for (int j : graph[i])
                reverseGraph[j].add(i);

        List<List<Integer>> components = new ArrayList<>();
        Arrays.fill(used, false);
        Collections.reverse(order);

        for (int u : order)
            if (!used[u]) {
                List<Integer> component = new ArrayList<>();
                dfs(reverseGraph, used, component, u);
                components.add(component);
            }

        return components;
    }

    static void dfs(List<Integer>[] graph, boolean[] used, List<Integer> res, int u) {
        used[u] = true;
        for (int v : graph[u])
            if (!used[v])
                dfs(graph, used, res, v);
        res.add(u);
    }

    // Usage example
    public static void main(String[] args) throws FileNotFoundException {
        List<Integer>[] g = new List[875715];
        for (int i = 0; i < g.length; ++i) {
            g[i] = new ArrayList<>();
        }

        String filename = "/Users/7times6/Downloads/SCC.txt";

        Scanner sc = new Scanner(new FileInputStream(filename));

        while (sc.hasNext()) {
            int v1 = sc.nextInt();
            int v2 = sc.nextInt();
            g[v1].add(v2);
        }

        List<List<Integer>> components = scc(g);

        System.out.println(components.size());
        Collections.sort(components, (o1, o2) -> o1.size() - o2.size());
        Collections.reverse(components);

        for (int i = 0; i < 5; ++i) {
            System.out.print(components.get(i).size() + ",");
        }
    }
}