designFile = "C:/Users/Gabriel/OneDrive/Documentos/Trabalhos IME/Extras/PIBITI FAPERJ/Projeto/BrushServo/PCB/BrushServo/PDNAnalyzer_Output/BrushServo_MG995/odb.tgz"

powerNets = ["VBAT_IS"]

groundNets = ["GND"]

excitation = [
{
"id": "0",
"type": "source",
"power_pins": [ ("R10", "2") ],
"ground_pins": [ ("C1", "2") ],
"voltage": 8.4,
"Rpin": 0,
}
,
{
"id": "1",
"type": "load",
"power_pins": [ ("Q2", "3") ],
"ground_pins": [ ("Q2", "1") ],
"current": 3,
"Rpin": 0.0333333333333333,
}
,
{
"id": "2",
"type": "load",
"power_pins": [ ("Q3", "3") ],
"ground_pins": [ ("Q3", "1") ],
"current": 3,
"Rpin": 0.0333333333333333,
}
]


voltage_regulators = []


# Resistors / Inductors

passives = []


# Material Properties:

tech = [

        {'name': 'TOP_SOLDER', 'DielectricConstant': 3.5, 'Thickness': 1.016E-05},
        {'name': 'TOP_LAYER', 'Conductivity': 47000000, 'Thickness': 3.556E-05},
        {'name': 'SUBSTRATE-1', 'DielectricConstant': 4.8, 'Thickness': 0.0006},
        {'name': 'BOTTOM_LAYER', 'Conductivity': 47000000, 'Thickness': 3.556E-05},
        {'name': 'BOTTOM_SOLDER', 'DielectricConstant': 3.5, 'Thickness': 1.016E-05}

       ]

special_settings = {'removecutoutsize' : 7.8 }


plating_thickness = 0.7
finished_hole_diameters = False
