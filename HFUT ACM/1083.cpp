#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn=20000+100;//点的数目
int tree[maxn<<4];
int li[maxn],ri[maxn];
int lisan[3*maxn];
bool visit[3*maxn];
void pushdown(int p) {
    tree[p<<1] = tree[(p<<1)|1] = tree[p];
    tree[p] = -1;
}

void update(int p, int l, int r, int x, int y, int v)
{
    if(x <= l && y >= r) { // 如果当前节点区间是染色区间的一部分，则直接染色
        tree[p] = v;
        return;
    }

    // 此时染色区间和节点区间可能是有一部分是重合的，所以需要对下层进行染色
    if (tree[p] != -1) pushdown(p);

    int mid = (l+r) >> 1;
    if (y <= mid) update(p<<1, l, mid, x, y, v);
    else if (x > mid) update((p<<1)|1, mid+1, r, x, y, v);
    else update(p<<1, l, mid, x, mid, v), update((p<<1)|1, mid+1, r, mid+1, y, v);
}

int ans;
void query(int p,int l,int r)
{
    if (tree[p] != -1) {
        if (!visit[tree[p]]) {
            ans++;
            visit[tree[p]] = true;
        }
        return;
    }

    if (l == r) return;

    int mid = (l+r) >> 1;
    query(p<<1, l, mid);
    query((p<<1)|1, mid+1, r);
}

int main()
{
    int T;
    scanf("%d", &T);
    int n;
    while(T--) {
        scanf("%d", &n);
        memset(tree, -1, sizeof(tree));
        memset(visit, false, sizeof(visit));
        int tot = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &li[i], &ri[i]);
            lisan[tot++] = li[i];
            lisan[tot++] = ri[i];
        }

        sort(lisan, lisan + tot); //tot是数组长度
        int m = unique(lisan, lisan + tot) - lisan; // 去重
        int t = m;
        for(int i = 1;i < t; i++) {
            if(lisan[i] - lisan[i-1] > 1) { lisan[m++]=lisan[i-1]+1; }
        }
        sort(lisan, lisan + m);

        // 开始染色
        for (int i = 0; i < n; i++) {
            // 找到第i次贴广告，左边界对应于离散后的区间的索引
            int x = lower_bound(lisan, lisan+m, li[i]) - lisan;
            // 找到第i次贴广告，右边界对应于离散后的区间的索引
            int y = lower_bound(lisan, lisan+m, ri[i]) - lisan;
            update(1, 0, m-1, x, y, i);
        }
        ans = 0;
        query(1, 0, m-1);
        printf("%d\n", ans);
    }
}
