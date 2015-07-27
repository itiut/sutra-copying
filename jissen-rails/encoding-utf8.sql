UPDATE pg_database SET datistemplate=false WHERE datname='template1';
DROP DATABASE template1;
CREATE DATABASE template1 WITH TEMPLATE = template0 ENCODING = 'UTF8';
UPDATE pg_database SET datistemplate=true WHERE datname='template1';
