// vector<lli> st(4*N,0),lazy(4*N,0);
struct segtree{
  lli n;
  vector<lli> st,lazy;
  void init(int nn){
    this->n = nn;
    st.resize(4*n,0);
    lazy.resize(4*n,0);
  }
  void build(lli s,lli e,lli node,vector<lli> &v){
    if(s == e){
      st[node] = v[s];
      return;
    }
    lli mid = (s+e)/2;
    build(s,mid,2*node+1,v);
    build(mid+1,e,2*node+2,v); 
    st[node] = st[2*node+1]+st[2*node+2];
  }
  lli query(lli s,lli e,lli l,lli r,lli node){
    if(s > r || e < l)  return 0;
    if(s >= l && e <= r)  return st[node];
    lli mid = (s+e)/2;
    lli q1 = query(s,mid,l,r,2*node+1);
    lli q2 = query(mid+1,e,l,r,2*node+2);
    return (q1+q2);
  }
  lli range_query(lli s,lli e,lli l,lli r,lli node){
    if(s > r || e < l)
      return 0;
    if(lazy[node] != 0){
      st[node] += lazy[node]*(e-s+1);
      if(s!=e){
        lazy[2*node+1] += lazy[node];
        lazy[2*node+2] += lazy[node];
      }
      lazy[node] = 0;
    }
    if(s >= l && e <= r)  return st[node];
    lli mid = (s+e)/2;
    lli q1 = range_query(s,mid,l,r,2*node+1);
    lli q2 = range_query(mid+1,e,l,r,2*node+2);
    return (q1+q2);
  }
  void update(lli s,lli e,lli node,lli idx,lli val){
    if(s == e){
      st[node] = val;
      return;
    }
    lli mid = (s+e)/2;
    if(idx <= mid)  update(s,mid,2*node+1,idx,val);
    else  update(mid+1,e,2*node+2,idx,val);
    st[node] = st[2*node+1] + st[2*node+2];
    return;
  }
  void range_update(lli s,lli e,lli node,lli l,lli r,lli val){
    if(s > r || e < l)  return;
    if(lazy[node] != 0){
      st[node] += lazy[node]*(e-s+1);
      if(s!=e){
        lazy[2*node+1] += lazy[node];
        lazy[2*node+2] += lazy[node];
      }
      lazy[node] = 0;
    }
    if(s >= l && e <= r){
      st[node] += val*(e-s+1);
      if(s!=e){
        lazy[2*node+1] += val;
        lazy[2*node+2] += val;
      }
      return;
    }
    lli mid = (s+e)/2;
    range_update(s,mid,2*node+1,l,r,val);
    range_update(mid+1,e,2*node+2,l,r,val); 
    st[node] = st[2*node+1]+st[2*node+2];
    return;
  }
  void build(vector<lli> &v){
    build(0,n-1,0,v);
  }
  lli query(lli l,lli r){
    return query(0,n-1,l,r,0);
  }
  lli range_query(lli l,lli r){
    return range_query(0,n-1,l,r,0);
  }
  void update(vector<lli> &v,lli idx,lli val){
    update(0,v.size()-1,0,idx,val);
  }
  void range_update(lli l,lli r,lli val){
    range_update(0,n-1,0,l,r,val);
  }
};