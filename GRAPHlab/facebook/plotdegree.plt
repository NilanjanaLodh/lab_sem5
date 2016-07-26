set terminal wxt 0 persist
set title 'Degree distibution'
set xlabel 'degree(no. of friends)'
set ylabel 'No. of users'
plot 'DegDistr' using 1:2  title 'Frequency' 

set terminal wxt 1 persist
set title 'Degree distibution'
set xlabel 'degree(d)'
set ylabel 'No. of users with atleast d friends'
plot 'DegDistr' using 1:3  title 'Cumulative Frequency' 

set terminal wxt 2 persist
set title 'Degree vs clustering coefficient'
set xlabel 'degree'
set ylabel 'clustering coefficient'
plot 'deg_cc_points' using 1:2 
