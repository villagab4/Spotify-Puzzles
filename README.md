#Spotify Puzzle Solutions

Descriptions of each puzzle can be found [here](https://labs.spotify.com/puzzles/)











#Cat vs Dog

May 28, 2017 Update

It is clear that solving this problem by finding the largest clique in the graph is NP complete and would take too long to discover. My next solution will be to try and create a bipartitie graph seeing as those graphs tend to have properties allowing for time-inexpensive operations. My first thought is to create a simple unweighted/undirected graph where voters DO CONFLICT. This is the opposite of my current implementation which connects voters with non-conflicting votes. Since each voter is either a cat lover, or a cat hater, each component of the said graph will be a bipartite graph. Then, I could applly some algorithms with bipartite graphs to reveal information about the complement of this graph. 

May 29, 2017 Update

Interestingly enough, by connecting vertices with conflicting voters, bipartite graphs are formed, and an interesting relationship is formed with the complemenet of this graph. Let n represent |V(G)| , then the maximum subset of non-conflicting voters is given by n - k, where k is the minimum vertex cover of G. This is true since each maximal subset of non-conflicting voters is represented as a minimal vertex cover for G. To clarify, a minimum vertex cover in G is the vertex cover of G having the smallest number of vertices of G ([source](http://mathworld.wolfram.com/MinimumVertexCover.html)). A vertex cover can be thought of as a subset S of vertices of V(G) such that every edge in E(G) has at least one member of S as an endpoint ([source](http://mathworld.wolfram.com/VertexCover.html)). Thus, a minimum vertex cover in G represents the minimum set of all conflicting votes, which is equivalent to n - m where m is the maximum set of non-conflicting votes. Nonetheless, by solving for the minimum vertex cover of G, we may solve for the maximum set of agreeable voters. Similar to the maximal clique problem, solving for the minimum vertex in a typical graph is NP-complete; however, when dealing with a bipartitie graph, Konig's theorem suggests that the number of edges in a maximum matching is equal to the number of vertices in a minimum vertex cover ([source](https://en.wikipedia.org/wiki/K%C5%91nig%27s_theorem_(graph_theory))). After researching how to find the maximum matching of a graph, I stumbled across the Hopcroft-Karp algorithm. Thankfully, the Hopcroft-Karp algorithm has a worst-case run time of O(|E(G)| * sqrt(n)). Note, in a complete bipartite graph, which happens to be the worst case, the number of edges is given by | E(G) | = n ^ 2, where n is the number of vertices. Thus, the worst-case time complexity for this algorithm is O(n ^ 2.5). A description of the Hopcroft-Karp algorithm may be found here https://brilliant.org/wiki/hopcroft-karp/

My rendition of the Hopcroft Karp algorithm is based on the one provided [here](http://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/)

