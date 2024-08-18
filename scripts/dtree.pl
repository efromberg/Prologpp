% dtree.pl
% https://saksagan.ceng.metu.edu.tr/courses/ceng242/documents/prolog/jrfisher/

% program P                       clause #         
 
p(a).                              % #1  
p(X) :- q(X), r(X).                % #2 
p(X) :- u(X).                      % #3  
 
q(X) :- s(X).                      % #4  


r(a).                              % #5  
r(b).                              % #6  


s(a).                              % #7  
s(b).                              % #8 
s(c).                              % #9  
 
u(d).                              % #10  

% ?- p(X).

