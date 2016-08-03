select emp_name,max(basic) from employee group by emp_name; 
select emp_name, min(basic) from employee group by emp_name;
