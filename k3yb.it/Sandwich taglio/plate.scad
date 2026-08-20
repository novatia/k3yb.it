plate_thickness = 1.5;
bottom_thickness = 3;
closed_thickness = 4;
spacer_thickness = 3.5;

plate_width  = 464.626;
plate_height = 159.826;

overlap = 0.2;


nice_w = 19;     // larghezza PCB nice!nano
nice_h = 35.0;     // lunghezza PCB


nice_x = 455-nice_w-51.5;
nice_y=116;


led_diameter = 3.3;      // diametro LED
led_clearance = 0.2;      // gioco

module led_hole(x, y)
{
    translate([x, y, -1])
        cylinder(
            h = 20,
            d = led_diameter + 2*led_clearance,
            $fn = 64
        );
}


module pcb()
{
    color("Black")
        cube([455, 150, 1.5]);
}

module plate()
{
    color([0.08,0.25,0.85])
    linear_extrude(height = plate_thickness)
        import("105-iso-MX-costar_1.5mm_DXF.dxf");
}

module bottom()
{
    color([0.75,0.75,0.78])
    linear_extrude(height = bottom_thickness)
        import("bottom_3mm_DXF.dxf");
}

module closed ()
{
    color([0.75,0.75,0.78])
    linear_extrude(height = closed_thickness)
        import("closed_4mm_DXF.dxf");
}


module spacer ()
{
    color([0.75,0.75,0.78])
    linear_extrude(height = spacer_thickness)
        import("closed_4mm_DXF.dxf");
}


module plate_part1()
{
    translate([0,0,20])
    
        intersection()
        {
            plate();

            translate([-1,-1,-1])
                cube([plate_width/3 + overlap + 1,
                      plate_height + 2,
                      plate_thickness + 2]);
        }

    
}

module spacer_part1()
{
    translate([0,0,10])
    intersection()
    {
        spacer();
        translate([-1,-1,-1])
            cube([plate_width/3 + overlap + 1,
                  plate_height + 2,
                  spacer_thickness + 2]);
     
    }
}


module closed_part1()
{
    translate([0,0,-10])
    intersection()
    {
        closed();
        translate([-1,-1,-1])
            cube([plate_width/3 + overlap + 1,
                  plate_height + 2,
                  closed_thickness + 2]);
     
    }
}

module bottom_part1()
{
    translate([0,0,-20])
    intersection()
    {
        bottom();
        translate([-1,-1,-1])
            cube([plate_width/3 + overlap + 1,
                  plate_height + 2,
                  bottom_thickness + 2]);
     
    }
      
}

module plate_part2()
{
    translate([0,0,20])
    intersection()
    {
        plate();
        translate([plate_width/3 - overlap,-1,-1])
            cube([plate_width/3 + overlap*2,
                  plate_height + 2,
                  plate_thickness + 2]);
        
       
    }
}

module spacer_part2()
{
    translate([0,0,10])
    intersection()
    {
        spacer();
        translate([plate_width/3 - overlap,-1,-1])
            cube([plate_width/3 + overlap*2,
                  plate_height + 2,
                  spacer_thickness + 2]);
    }
}


module closed_part2()
{
    translate([0,0,-10])
    intersection()
    {
        closed();
        translate([plate_width/3 - overlap,-1,-1])
            cube([plate_width/3 + overlap*2,
                  plate_height + 2,
                  closed_thickness + 2]);
    }
}

module bottom_part2()
{
    translate([0,0,-20])
    intersection()
    {
        bottom();
        translate([plate_width/3 - overlap,-1,-1])
            cube([plate_width/3 + overlap*2,
                  plate_height + 2,
                  bottom_thickness + 2]);
    }
}

module plate_part3()
{
    translate([0,0,20])
    {
        difference()
        {
            intersection()
            {
                plate();

                translate([2*plate_width/3 - overlap,-1,-1])
                    cube([plate_width,
                          plate_height + 2,
                          plate_thickness + 2]);
            }

            color("Black")
                translate([nice_x, nice_y, -1])
                    cube([nice_w, nice_h, 5]);
            
                led_hole(417, 150-12);
                led_hole(423, 150-12);
                led_hole(429, 150-12);
                led_hole(435, 150-12);
        }
    }
}

module spacer_part3()
{
    translate([0,0,10])
      difference()
      {
            intersection()
            {
                
                 spacer();
                translate([2*plate_width/3 - overlap,-1,-1])
                    cube([plate_width,
                          plate_height + 2,
                           spacer_thickness + 2]);
                
               
            }
            
               color("Black")
                translate([nice_x, nice_y, -1])
                    cube([nice_w, nice_h, 5]);
      }
}


module closed_part3()
{
    translate([0,0,-10])
    intersection()
    {
        
        closed();
        translate([2*plate_width/3 - overlap,-1,-1])
            cube([plate_width,
                  plate_height + 2,
                  closed_thickness + 2]);
        
         
    }
}



module bottom_part3()
{
    translate([0,0,-20])
    intersection()
    {
        
         bottom();
        translate([2*plate_width/3 - overlap,-1,-1])
            cube([plate_width,
                  plate_height + 2,
                  bottom_thickness + 2]);
        
         
    }
}

// Scegli quale esportare
plate_part1();
plate_part2();
plate_part3();

//spacer_part1();
//spacer_part2();
//spacer_part3();

//pcb();

//closed_part1();
//closed_part2();
//closed_part3();

//bottom_part1();
//bottom_part2();
//bottom_part3();

