PROGRAM com::examples::types::types01(
            VAR p1 AS Integer : "IAS/DM/Default",
            VAR input AS Customer : "http://www.examples.org/akc",
            VAR output AS Customer : "http://www.examples.org/akc")  BEGIN

    VAR t AS ExampleType : "http://www.examples.org/types";
    VAR ts AS SubExampleType : "http://www.examples.org/types";
    VAR sa AS SubAddress : "http://www.examples.org/types";
    VAR ss AS ExampleTypeDef : "http://www.examples.org/types";
    VAR a AS Address : "http://www.examples.org/akc";

    t.p2=NEW Address : "http://www.examples.org/akc"     BEGIN
      street="Typowa";
      block=102;
    END;

    WITH t.p2 DO
      BEGIN
        street=((street + " ") + street);
      END;

    ts.p4=NEW Address : "http://www.examples.org/akcf";
    ts.p4.street="SubStreet";
    ts.p4.block=201;
    ss="Extra delivery";
    sa.info=ss;
    sa.alternate=NEW Address : "http://www.examples.org/akcf";
    sa.alternate.street="SubStreet";
    sa.alternate.block=201;
    output=COPYOF(input);
    a=t.p2;
    t.p2=NEW Address : "http://www.examples.org/akc";
    output.address=a;
    output.address=COPYOF(ts.p4);
    output.address=COPYOF(sa);
  END;
