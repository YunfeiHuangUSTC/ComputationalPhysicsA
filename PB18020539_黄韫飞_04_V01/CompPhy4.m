low=-5;
up=5;
f=@(x) exp(-2*atan(1+x)).*sqrt(2+2*x+x.^2);
A=quadgk(f,low,up);
x=linspace(low,up,101);
f=@(x) 1/A*exp(-2*atan(1+x)).*sqrt(2+2*x+x.^2);
xi=zeros(1,101);
RandNum = RandGen16807{:,1};
p=zeros(1,numel(RandNum));
for i=1:1:101
xi(i)=quadgk(f,low,x(i));
end 
for k=1:1:numel(RandNum)
    p(k)=interp1(xi,x,RandNum(k),'spline');
end
histogram(p);