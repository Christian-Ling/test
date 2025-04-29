#include "mst.h"
#include "binaryHeap.h"       // Custom binary heap
#include "binomialHeap.h"   // Custom binomial heap

// ===== QuickUnion =====
QuickUnion::QuickUnion(int n) 
{
    parent.resize(n);
    for (int i = 0; i < n; ++i) {
        parent[i] = i; 
    }
}

int QuickUnion::find(int x) 
{
    while (parent[x] != x) {
        parent[x] = x; 
    }
    return x;
}

void QuickUnion::Union(int x, int y) 
{
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

// ===== UnionFind =====
UnionFind::UnionFind(int n) 
{
    parent.resize(n);
    rank.resize(n, 1); 
    for (int i = 0; i < n; i++) {
        parent[i] = i; 
    }
}

int UnionFind::find(int x) 
{
    if (parent[x] != x) {
        parent[x] = find(parent[x]); 
    }
    return parent[x];
}

void UnionFind::Union(int x, int y) 
{
    int rootX = find(x);
    int rootY = find(y);
    
    if (rootX == rootY) 
        return; 
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
            rank[rootY] += rank[rootX];
        } else {
            parent[rootY] = rootX;
            rank[rootX] += rank[rootY];
        }

}

// ===== MST =====
MST::MST(int vertices)
{
    n = vertices;
}

void MST::addEdge(int u, int v, int weight) 
{
    edges.push_back({u, v, weight});
}

int MST::kruskalV1() 
{
    HEAP heap(edges.size());
    for (const Edge& e : edges) {
        heap.insertH(e);
    }

    QuickUnion uf(n);
    int mstCost = 0;
    int edgesUsed = 0;

    while (edgesUsed < n - 1 && heap.peek().weight != -1) {
        Edge e = heap.peek();
        heap.deleteMin();

        int uRoot = uf.find(e.src);
        int vRoot = uf.find(e.dest);

        if (uRoot != vRoot) {
            uf.Union(uRoot, vRoot);
            mstCost += e.weight;
            edgesUsed++;
        }
    }
    return mstCost;
}

int MST::kruskalV2() 
{
    BinomialHeap heap;

    for ( int i = 0; i < edges.size(); i++) {
        heap.insert(edges[i].weight);
    }

    vector<vector<Edge>> weightToEdges(10001);

    for (const Edge& e : edges) {
        weightToEdges[e.weight].push_back(e);
    }

    UnionFind uf(n);
    int mstCost = 0;
    int edgesUsed = 0;

    while (edgesUsed < n - 1 && heap.findMin() != -1) {
      int w = heap.findMin();
        heap.deleteMin();

        if (weightToEdges[w].empty()) {
            continue;
        }
        Edge e = weightToEdges[w].back();
        weightToEdges[w].pop_back();



        int uRoot = uf.find(e.src);
        int vRoot = uf.find(e.dest);

        if (uRoot != vRoot) {
            uf.Union(uRoot, vRoot);
            mstCost += e.weight;
            edgesUsed++;
        }
    }

    return mstCost;
}
