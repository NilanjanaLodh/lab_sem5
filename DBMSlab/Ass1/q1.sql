CREATE TABLE employee(
    emp_code char(50) ,
    emp_name char(40),
    dept_code char(5),
    desig_code char(5),
    gender char(1),
    address varchar(50),
    city char(20),
    state char(20),
    pin char(6),
    basic number,
    jn_dt date,
    PRIMARY KEY (emp_code)
);
