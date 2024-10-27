//----------Task_9----------//

create table SMA_t (x number(3), s varchar2(50)); 

//----------Task_11----------//

insert into SMA_t (x, s) values (1, 'Строка 1'); 
insert into SMA_t (x, s) values (2, 'Строка 2'); 
insert into SMA_t (x, s) values (3, 'Строка 3'); 

commit;

//----------Task_12----------//

update SMA_t set s = 'Измененная строка' where x = 2 OR x = 3;

commit;

//----------Task_13----------//

select * from SMA_t;
select * from SMA_t where x = 1;
select count(*) as totalRows from SMA_t;
select sum(x) as TotalSum from SMA_t;

//----------Task_14----------//

delete from SMA_t where x = 1;
commit;

//----------Task_15----------//

alter table SMA_t add constraint pk_sma_t primary key (x);
create table SMA_t1 (id number(3) primary key, some_info varchar(20), x number(3), constraint fk_sma_t_x foreign key (x) references SMA_t(x));

insert into SMA_t1 (id, some_info, x) values (1, 'Info 1', 2);
insert into SMA_t1 (id, some_info, x) values (2, 'Info 2', 3);

//----------Task_16----------//

select * from SMA_t left outer join SMA_t1 on SMA_t.x = SMA_t1.x;
select * from SMA_t right outer join SMA_t1 on SMA_t.x = SMA_t1.x;
select * from SMA_t inner join SMA_t1 on SMA_t.x = SMA_t1.x;

//----------Task_18----------//

drop table SMA_t;
drop table SMA_t1;