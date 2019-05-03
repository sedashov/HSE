# finding connectivity components in a graph using dfs
import sys


def dfs(graph, now):
    discovered[now] = 1
    component.append(now + 1)
    for vertex in graph[now]:
        if not discovered[vertex] and vertex != now:
            dfs(graph, vertex)


n, m = map(int, input().split())
sys.setrecursionlimit(100000000)
g = []
for i in range(n):
    g.append([])
for i in range(m):
    v1, v2 = map(int, input().split())
    g[v1 - 1].append(v2 - 1)
    g[v2 - 1].append(v1 - 1)
discovered = [0] * n
components = []
for i in range(len(discovered)):
    if not discovered[i]:
        component = []
        dfs(g, i)
        components.append(component)
print(len(components))
for comp in components:
    print(len(comp))
    print(*comp)

