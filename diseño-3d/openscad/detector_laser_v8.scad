// ==========================================================
// DETECTOR LÁSER (VL53L0X / GY-530) - V8 (listo para imprimir)
// Diseño modular y sellado: BASE DE ANCLAJE + CUBIERTA
// ==========================================================

// ---------- QUÉ MOSTRAR / EXPORTAR ----------
// "explosionado" | "ensamblado" | "base" | "cubierta" | "vidrio" | "reporte"
// Para imprimir: exporta "base" y "cubierta" por separado (STL en mm, escala 100 %).
pieza      = "explosionado";
separacion = 70;        // separación de la cubierta en la vista explosionada
corte      = false;     // true = corta por x=0 para ver el interior
mostrar_electronica = true;   // maquetas de batería / PCB (solo visual)

$fn = 90;
eps = 0.01;

// ---------- BASE DE ANCLAJE ----------
h_base      = 8;        // placa gruesa
r_brida     = 80;       // V8: 75 -> 80 para que quepa la arandela del perno
d_perno     = 9.0;      // V8: agujero para perno M8 con holgura (antes 8.0 = sin holgura)
r_perno     = d_perno/2;
r_perno_pos = 69;       // V8: 65 -> 69, la arandela M8 (Ø16) queda fuera de la cubierta
d_arandela  = 16;       // arandela M8 estándar

// ---------- CUBIERTA ----------
r_base        = 60;     // radio exterior del faldón
alt_faldon    = 16;     // tramo vertical antes de la rampa
alto_cubierta = 32;     // altura total de la cubierta sobre la base
r_tope        = 30;
dy_tope       = 10;
espesor_techo = 3;
r_int_base    = 49;     // faldón de 11 mm: aloja tornillos y apoya el O-ring
r_int_tope    = 25;
z_tope_ext    = h_base + alto_cubierta;

// ---------- UNIÓN Y SELLADO ----------
r_tornillo  = 57;       // 4 M3 desde abajo, FUERA del sello
oring_d     = 2.5;      // sección del O-ring (cordón de 2.5 mm)
r_oring     = 51.5;     // radio medio del O-ring
ancho_ranura = 3.5;     // ~1.4 x sección
prof_ranura  = 2.0;     // ~0.8 x sección (compresión ~20 %)

// ---------- IMPRESIÓN ----------
chaflan_pie  = 0.4;     // V8: chaflán anti "pata de elefante" en la cara que va sobre la cama
margen_pared = 2.0;     // V8: holgura mínima electrónica <-> pared interior de la cubierta

// ---------- POSICIÓN DE LA ELECTRÓNICA (V8: todo dentro del círculo r_int_base) ----------
y_pcb        = -22;     // centro en Y de la PCB ESP8266 (V7: -24, tocaba la pared)
y_bat0       = 4;       // borde delantero del soporte 18650 (V7: 10, chocaba con el faldón)
bat_largo    = 74;      // soporte 18650 en X
bat_ancho    = 24;      // soporte 18650 en Y
tope_largo   = 16;      // V8: topes cortos (V7: 24) para no tocar el faldón

// ---------- COMPARTIMENTACIÓN ----------
y_tabique    = -3;      // V7: -6. Pared entre PCB (frente) y batería (fondo)
alto_tabique = 16;
grosor_tabique = 3;
tabique_x0   = -40;     // tabique parcial: deja paso de cables en +X
tabique_x1   = 12;

// ---------- SENSOR VL53L0X ----------
t_sensor      = 0.7;
r_vidrio      = 10;
grosor_vidrio = 2;
prof_asiento  = 2.4;
r_ventana     = 7;
labio         = 1.2;
pcb_x         = 27;     // placa GY-530 + holgura (¡mídela!)
pcb_y         = 14;
prof_bolsillo = 6;
pared_bolsillo = 4;
pcb_desp_x    = 0;

// ==========================================================
// GEOMETRÍA DE LA RAMPA
// ==========================================================
// ---------- COMPROBACIONES AUTOMÁTICAS (fallan si algo no cabe) ----------
assert(r_perno_pos - d_arandela/2 >= r_base + 0.5, "Arandela del perno choca con la cubierta");
assert(r_perno_pos + r_perno + 3 <= r_brida,        "Agujero de anclaje muy cerca del borde");
assert(sqrt(29*29 + (abs(y_pcb) + 15.5)*(abs(y_pcb) + 15.5)) + margen_pared <= r_int_base,
       "La PCB toca la pared interior");
assert(sqrt(pow(bat_largo/2,2) + pow(y_bat0 + bat_ancho,2)) + margen_pared <= r_int_base,
       "El soporte de batería toca la pared interior");
assert(r_oring - ancho_ranura/2 > r_int_base,      "Ranura de O-ring dentro del hueco");

ya = -r_base;               za = h_base + alt_faldon;
yb = dy_tope - r_tope;      zb = z_tope_ext;
ang_rampa  = atan2(zb - za, yb - ya);
ang_sensor = ang_rampa;

y_s = ya + t_sensor * (yb - ya);
z_s = za + t_sensor * (zb - za);

module marco_sensor() {
    translate([0, y_s, z_s]) rotate([ang_sensor, 0, 0]) children();
}

// ==========================================================
// CUBIERTA (pieza superior)
// ==========================================================
module envolvente_cubierta() {
    hull() {
        translate([0, 0, h_base]) cylinder(h = alt_faldon, r = r_base);
        translate([0, dy_tope, z_tope_ext - 2]) cylinder(h = 2, r = r_tope);
    }
}

module cavidad_cubierta() {   // abierta por abajo; trasera totalmente cerrada
    hull() {
        translate([0, 0, h_base - 1]) cylinder(h = alt_faldon + 1, r = r_int_base);
        translate([0, dy_tope, z_tope_ext - espesor_techo - 2])
            cylinder(h = 2, r = r_int_tope);
    }
}

module refuerzo_sensor() {
    z_tot = prof_asiento + labio + prof_bolsillo;
    marco_sensor()
        translate([-(pcb_x + 2*pared_bolsillo)/2 + pcb_desp_x,
                   -(pcb_y + 2*pared_bolsillo)/2, -z_tot])
            cube([pcb_x + 2*pared_bolsillo, pcb_y + 2*pared_bolsillo, z_tot + 3]);
}

module ventana_sensor() {
    marco_sensor() {
        translate([0, 0, -prof_asiento]) cylinder(h = 40, r = r_vidrio + 0.2);
        translate([0, 0, -prof_asiento - labio - 1])
            cylinder(h = prof_asiento + labio + 45, r = r_ventana);
        translate([-pcb_x/2 + pcb_desp_x, -pcb_y/2,
                   -(prof_asiento + labio) - prof_bolsillo - eps])
            cube([pcb_x, pcb_y, prof_bolsillo + eps]);
    }
}

module pilotos_cubierta() {   // agujeros guía M3 en el faldón (ciegos)
    for (a = [0 : 90 : 270])
        rotate([0, 0, a]) translate([r_tornillo, 0, h_base - eps])
            cylinder(h = 10, d = 2.6);
}

module cubierta() {
    difference() {
        union() {
            difference() { envolvente_cubierta(); cavidad_cubierta(); }
            intersection() { envolvente_cubierta(); refuerzo_sensor(); }
        }
        ventana_sensor();
        pilotos_cubierta();
        // chaflán exterior del borde que apoya en la cama (cubierta impresa boca abajo)
        rotate_extrude()
            polygon([[r_base - chaflan_pie, h_base - eps], [r_base + 1, h_base - eps],
                     [r_base + 1, h_base + chaflan_pie + 1]]);
    }
}

// ==========================================================
// BASE DE ANCLAJE (pieza inferior)
// ==========================================================
module ranura_oring() {
    translate([0, 0, h_base - prof_ranura])
        rotate_extrude()
            translate([r_oring - ancho_ranura/2, 0])
                square([ancho_ranura, prof_ranura + eps]);
}

module tabique() {
    translate([tabique_x0, y_tabique - grosor_tabique/2, h_base - eps])
        cube([tabique_x1 - tabique_x0, grosor_tabique, alto_tabique]);
}

module soportes_base() {
    // 4 apoyos para la PCB del ESP8266
    for (x = [-22, 22], y = [y_pcb - 11, y_pcb + 11])
        translate([x, y, h_base - eps]) cylinder(h = 3, d = 6);
    // 2 topes para el soporte de la 18650 (cortos y centrados: no tocan el faldón)
    yt = y_bat0 + (bat_ancho - tope_largo)/2;
    translate([ bat_largo/2,     yt, h_base - eps]) cube([3, tope_largo, 6]);
    translate([-bat_largo/2 - 3, yt, h_base - eps]) cube([3, tope_largo, 6]);
}

module base_anclaje() {
    difference() {
        union() {
            // disco con chaflán inferior (evita la pata de elefante)
            rotate_extrude()
                polygon([[0, 0], [r_brida - chaflan_pie, 0], [r_brida, chaflan_pie],
                         [r_brida, h_base], [0, h_base]]);
            tabique();
            soportes_base();
        }
        // 4 pernos grandes de anclaje al suelo
        for (i = [45 : 90 : 315])
            rotate([0, 0, i]) translate([r_perno_pos, 0, -1])
                cylinder(h = h_base + 2, r = r_perno);
        // 4 tornillos M3 pasantes (avellanados por abajo)
        for (a = [0 : 90 : 270])
            rotate([0, 0, a]) translate([r_tornillo, 0, -eps]) {
                cylinder(h = h_base + 0.02, d = 3.4);
                cylinder(h = 1.6, d1 = 6.4, d2 = 3.4);
            }
        ranura_oring();
    }
}

// ==========================================================
// COMPONENTES DE MAQUETA (no se imprimen)
// ==========================================================
module oring() {
    color("black")
    translate([0, 0, h_base - prof_ranura + oring_d/2])
        rotate_extrude() translate([r_oring, 0]) circle(d = oring_d);
}

module vidrio() {
    color("cyan", 0.5)
    marco_sensor() translate([0, 0, -prof_asiento]) cylinder(h = grosor_vidrio, r = r_vidrio);
}

module gy530_demo() {
    color("mediumblue")
    marco_sensor() translate([-25/2 + pcb_desp_x, -11/2, -(prof_asiento + labio) - 1.6])
        cube([25, 11, 1.6]);
}

module electronica_demo() {
    // PCB ESP8266 (~58x31) sobre los apoyos
    color("royalblue") translate([-29, y_pcb - 15.5, h_base + 3]) cube([58, 31, 1.6]);
    color("dimgray")   translate([-8, y_pcb - 8, h_base + 4.6]) cube([16, 16, 3]);
    // soporte de batería 18650
    color("dimgray") {
        translate([-bat_largo/2, y_bat0, h_base]) cube([bat_largo, bat_ancho, 3]);
        translate([-bat_largo/2, y_bat0, h_base]) cube([4, bat_ancho, 14]);
        translate([ bat_largo/2 - 4, y_bat0, h_base]) cube([4, bat_ancho, 14]);
    }
    // celda 18650 (verde)
    color("limegreen")
        translate([0, y_bat0 + bat_ancho/2, h_base + 3 + 9.25]) rotate([0, 90, 0])
            cylinder(h = 65, r = 9.25, center = true);
}

module seccion() {
    if (corte) difference() { children(); translate([0, -200, -50]) cube([200, 400, 500]); }
    else children();
}

module gris() color("#8d9298") children();

// ==========================================================
// SALIDA
// ==========================================================
seccion() {
    if (pieza == "explosionado") {
        gris() base_anclaje();
        if (mostrar_electronica) electronica_demo();
        translate([0, 0, separacion * 0.3]) oring();
        translate([0, 0, separacion]) {
            gris() cubierta();
            vidrio();
            if (mostrar_electronica) gy530_demo();
        }
    }
    else if (pieza == "ensamblado") {
        gris() base_anclaje();
        gris() cubierta();
        oring(); vidrio();
        if (mostrar_electronica) { electronica_demo(); gy530_demo(); }
    }
    else if (pieza == "base")     base_anclaje();
    else if (pieza == "cubierta") translate([0, 0, -h_base]) cubierta();  // imprimir boca abajo sobre el faldón
    else if (pieza == "vidrio")   vidrio();
    else if (pieza == "reporte") {
        echo("=== MEDIDAS PARA IMPRIMIR (mm) ===");
        echo(base_diametro = 2*r_brida, base_altura_con_tabique = h_base + alto_tabique);
        echo(cubierta_diametro = 2*r_base, cubierta_altura = alto_cubierta);
        echo(perno_agujero = d_perno, perno_circulo = 2*r_perno_pos);
        echo(oring_interior_aprox = 2*(r_oring - oring_d/2), oring_seccion = oring_d);
        echo(angulo_rampa_grados = ang_rampa);
    }
}
