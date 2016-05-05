PROGRAM com::examples::basic::datetime(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN

    VAR i AS Integer : "IAS/DM/Default";

    output=COPYOF(input);
    output.birth="2013-09-08T12:46:39+0200";

    FOR i = 1 TO 10 DO
      BEGIN

        VAR a AS Address : "http://www.examples.org/akc";

        a=NEW Address : "http://www.examples.org/akcf";
        a.street=(output.birth + i);
        a.block=i;
        output.address=a;
      END;

    output.address[1].street=(output.birth + (((10 * 365) * 24) * 3600));
    output.address[2]=NEW Address : "http://www.examples.org/akc";
    output.address[2].street=std::modifytime(output.birth,10,10,10);
    output.address[3].street=std::modifydate(output.birth,10,10,10);
    output.address[4].street=(output.birth - (((10 * 365) * 24) * 3600));
    output.someDate="2001-02-03";
    output.someTime="10:20:30";
    output.someDate=(output.someDate + ((10 * 24) * 3600));
    output.someTime=((output.someTime + (3600 * 3)) + "01:02:03");
    output.info=((((("Date: " + output.someDate) + ", Time: ") + output.someTime) + ", TS: ") + output.birth);
  END;
