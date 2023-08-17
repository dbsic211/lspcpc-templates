int read(){
  int x=0,f=1;
  char c=getchar();
  while(c<'0'||c>'9'){
    if(c=='-'){
      f=-1;
    }
    c=getchar();
  }
  while(c>='0'&&c<='9'){
    x=(x<<3)+(x<<1)+c-'0';
    c=getchar();
  }
  return x*f;
}
void write(int x){
  if(x<0) x=-x;
  if(x>9) write(x/10);
  putchar(x%10+'0');
}
