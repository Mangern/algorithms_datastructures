ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll g = exgcd(b,a%b,x1,y1);
    x = y1;
    y = x1 - y1 * (a/b);
    return g;
}

ll inv(ll a, ll f) {
    a = (a%f+f)%f;
    ll x,y;
    exgcd(a,f, x,y);

    x = (x%f+f)%f;
    return x;
}



