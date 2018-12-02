import zx


def init_text():

    #file="data/ttf/dejavu-nerd.ttf_pointsize80.tga",
    zx.tex_load(
            file="data/ttf/PressStart2P.ttf_pointsize80.tga",
            name="text")

    tiles = [
    "C0", "C1", "C2", "C3", "C4", "C5", "C6", "C7",
    "C8", "C9", "C10", "C11", "C12", "C13", "C14", "C15",
    "C16", "C17", "C18", "C19", "C20", "C21", "C22", "C23",
    "C24", "C25", "C26", "C27", "C28", "C29", "C30", "C31",
    "C32", "C33", "C34", "C35",
    "C36", "C37", "C38", "C39", "C40", "C41", "C42", "C43", "C44",
    "C45", "C46", "C47", "C48", "C49", "C50", "C51", "C52", "C53",
    "C54", "C55", "C56", "C57", "C58", "C59", "C60", "C61", "C62",
    "C63", "C64", "C65", "C66", "C67", "C68", "C69", "C70", "C71",
    "C72", "C73", "C74", "C75", "C76", "C77", "C78", "C79", "C80",
    "C81", "C82", "C83", "C84", "C85", "C86", "C87", "C88", "C89",
    "C90", "C91", "C92", "C93", "C94", "C95", "C96", "C97", "C98",
    "C99", "C100", "C101", "C102", "C103", "C104", "C105", "C106", "C107",
    "C108", "C109", "C110", "C111", "C112", "C113", "C114", "C115", "C116",
    "C117", "C118", "C119", "C120", "C121", "C122", "C123", "C124", "C125",
    "C126", "C127", "C128", "C129", "C130", "C131", "C132", "C133", "C134",
    "C135", "C136", "C137", "C138", "C139", "C140", "C141", "C142", "C143",
    "C144", "C145", "C146", "C147", "C148", "C149", "C150", "C151", "C152",
    "C153", "C154", "C155", "C156", "C157", "C158", "C159", "C160", "C161",
    "C162", "C163", "C164", "C165", "C166", "C167", "C168", "C169", "C170",
    "C171", "C172", "C173", "C174", "C175", "C176", "C177", "C178", "C179",
    "C180", "C181", "C182", "C183", "C184", "C185", "C186", "C187", "C188",
    "C189", "C190", "C191", "C192", "C193", "C194", "C195", "C196", "C197",
    "C198", "C199", "C200", "C201", "C202", "C203", "C204", "C205", "C206",
    "C207", "C208", "C209", "C210", "C211", "C212", "C213", "C214", "C215",
    "C216", "C217", "C218", "C219", "C220", "C221", "C222", "C223", "C224",
    "C225", "C226", "C227", "C228", "C229", "C230", "C231", "C232", "C233",
    "C234", "C235", "C236", "C237", "C238", "C239", "C240", "C241", "C242",
    "C243", "C244", "C245", "C246", "C247", "C248", "C249", "C250", "C251",
    "C252", "C253", "C254", "C255", "C256", "C257", "C258", "C259", "C260",
    "C261", "C262", "C263", "C264", "C265", "C266", "C267", "C268", "C269",
    "C270", "C271", "C272", "C273", "C274", "C275", "C276", "C277", "C278",
    "C279", "C280", "C281", "C282", "C283", "C284", "C285", "C286", "C287",
    "C288", "C289", "C290", "C291", "C292", "C293", "C294", "C295", "C296",
    "C297", "C298", "C299", "C300", "C301", "C302", "C303", "C304", "C305",
    "C306", "C307", "C308", "C309", "C310", "C311", "C312", "C313", "C314",
    "C315", "C316", "C317", "C318", "C319", "C320", "C321", "C322", "C323",
    "C324", "C325", "C326", "C327", "C328", "C329", "C330", "C331", "C332",
    "C333", "C334", "C335", "C336", "C337", "C338", "C339", "C340", "C341",
    "C342", "C343", "C344", "C345", "C346", "C347", "C348", "C349",
    ]

    zx.tile_load_arr(tex_name="text",
                     width=8, height=8,
                     arr=tiles)


def init_light():
    zx.tex_load(
            file="data/gfx/light.tga",
            name="light")

def init_16x16():
    zx.tex_load(
            file="data/gfx/16x16.tga",
            name="16x16")

    tiles = [
            "player1.1",
            "player1.2",
            "player1.3",
            "player1.4",
            "player1.5",
            "player1.6",
            "monst1.1",
            "monst1.2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "floor1.1",
            "floor1.2",
            "floor1.3",
            "floor1.4",
            "floor1.5",
            "floor1.6",
            "floor1.7",
            "floor1.8",
            "floor1.9",
            "floor1.10",
            "floor1.11",
            "floor1.12",
            "floor1.13",
            "floor1.14",
            "floor1.15",
            "floor1.16",
            "floor1.17",
            "floor1.18",
            "floor1.19",
            "floor1.20",
            "floor1.21",
            "floor1.22",
            "floor1.23",
            "floor1.24",
            "floor1.25",
            "floor1.26",
            "floor1.27",
            "floor1.28",
            "floor1.29",
            "floor1.30",
            "floor1.31",
            "floor1.32",
            ########################################################
            "floor2.1",
            "floor2.2",
            "floor2.3",
            "floor2.4",
            "floor2.5",
            "floor2.6",
            "floor2.7",
            "floor2.8",
            "floor2.9",
            "floor2.10",
            "floor2.11",
            "floor2.12",
            "floor2.13",
            "floor2.14",
            "floor2.15",
            "floor2.16",
            "floor2.17",
            "floor2.18",
            "floor2.19",
            "floor2.20",
            "floor2.21",
            "floor2.22",
            "floor2.23",
            "floor2.24",
            "floor2.25",
            "floor2.26",
            "floor2.27",
            "floor2.28",
            "floor2.29",
            "floor2.30",
            "floor2.31",
            "floor2.32",
            ########################################################
            "floor3.1",
            "floor3.2",
            "floor3.3",
            "floor3.4",
            "floor3.5",
            "floor3.6",
            "floor3.7",
            "floor3.8",
            "floor3.9",
            "floor3.10",
            "floor3.11",
            "floor3.12",
            "floor3.13",
            "floor3.14",
            "floor3.15",
            "floor3.16",
            "floor3.17",
            "floor3.18",
            "floor3.19",
            "floor3.20",
            "floor3.21",
            "floor3.22",
            "floor3.23",
            "floor3.24",
            "floor3.25",
            "floor3.26",
            "floor3.27",
            "floor3.28",
            "floor3.29",
            "floor3.30",
            "floor3.31",
            "floor3.32",
            ########################################################
            "floor4.1",
            "floor4.2",
            "floor4.3",
            "floor4.4",
            "floor4.5",
            "floor4.6",
            "floor4.7",
            "floor4.8",
            "floor4.9",
            "floor4.10",
            "floor4.11",
            "floor4.12",
            "floor4.13",
            "floor4.14",
            "floor4.15",
            "floor4.16",
            "floor4.17",
            "floor4.18",
            "floor4.19",
            "floor4.20",
            "floor4.21",
            "floor4.22",
            "floor4.23",
            "floor4.24",
            "floor4.25",
            "floor4.26",
            "floor4.27",
            "floor4.28",
            "floor4.29",
            "floor4.30",
            "floor4.31",
            "floor4.32",
            ########################################################
            "floor5.1",
            "floor5.2",
            "floor5.3",
            "floor5.4",
            "floor5.5",
            "floor5.6",
            "floor5.7",
            "floor5.8",
            "floor5.9",
            "floor5.10",
            "floor5.11",
            "floor5.12",
            "floor5.13",
            "floor5.14",
            "floor5.15",
            "floor5.16",
            "floor5.17",
            "floor5.18",
            "floor5.19",
            "floor5.20",
            "floor5.21",
            "floor5.22",
            "floor5.23",
            "floor5.24",
            "floor5.25",
            "floor5.26",
            "floor5.27",
            "floor5.28",
            "floor5.29",
            "floor5.30",
            "floor5.31",
            "floor5.32",
            ########################################################
            "floor6.1",
            "floor6.2",
            "floor6.3",
            "floor6.4",
            "floor6.5",
            "floor6.6",
            "floor6.7",
            "floor6.8",
            "floor6.9",
            "floor6.10",
            "floor6.11",
            "floor6.12",
            "floor6.13",
            "floor6.14",
            "floor6.15",
            "floor6.16",
            "floor6.17",
            "floor6.18",
            "floor6.19",
            "floor6.20",
            "floor6.21",
            "floor6.22",
            "floor6.23",
            "floor6.24",
            "floor6.25",
            "floor6.26",
            "floor6.27",
            "floor6.28",
            "floor6.29",
            "floor6.30",
            "floor6.31",
            "floor6.32",
            ########################################################
            "floor7.1",
            "floor7.2",
            "floor7.3",
            "floor7.4",
            "floor7.5",
            "floor7.6",
            "floor7.7",
            "floor7.8",
            "floor7.9",
            "floor7.10",
            "floor7.11",
            "floor7.12",
            "floor7.13",
            "floor7.14",
            "floor7.15",
            "floor7.16",
            "floor7.17",
            "floor7.18",
            "floor7.19",
            "floor7.20",
            "floor7.21",
            "floor7.22",
            "floor7.23",
            "floor7.24",
            "floor7.25",
            "floor7.26",
            "floor7.27",
            "floor7.28",
            "floor7.29",
            "floor7.30",
            "floor7.31",
            "floor7.32",
            ########################################################
            "floor8.1",
            "floor8.2",
            "floor8.3",
            "floor8.4",
            "floor8.5",
            "floor8.6",
            "floor8.7",
            "floor8.8",
            "floor8.9",
            "floor8.10",
            "floor8.11",
            "floor8.12",
            "floor8.13",
            "floor8.14",
            "floor8.15",
            "floor8.16",
            "floor8.17",
            "floor8.18",
            "floor8.19",
            "floor8.20",
            "floor8.21",
            "floor8.22",
            "floor8.23",
            "floor8.24",
            "floor8.25",
            "floor8.26",
            "floor8.27",
            "floor8.28",
            "floor8.29",
            "floor8.30",
            "floor8.31",
            "floor8.32",
            ########################################################
            "corridor1.1",
            "corridor1.2",
            "corridor1.3",
            "corridor1.4",
            "corridor1.5",
            "corridor1.6",
            "corridor1.7",
            "corridor1.8",
            "corridor1.9",
            "corridor1.10",
            "corridor1.11",
            "corridor1.12",
            "corridor1.13",
            "corridor1.14",
            "corridor1.15",
            "corridor1.16",
            "corridor1.17",
            "corridor1.18",
            "corridor1.19",
            "corridor1.20",
            "corridor1.21",
            "corridor1.22",
            "corridor1.23",
            "corridor1.24",
            "corridor1.25",
            "corridor1.26",
            "corridor1.27",
            "corridor1.28",
            "corridor1.29",
            "corridor1.30",
            "corridor1.31",
            "corridor1.32",
            ########################################################
            "lava1.1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.1.2x1.1",
            "wall1.1.2x1.2",
            "wall1.1.6x6.1",
            "wall1.1.6x6.2",
            "wall1.1.6x6.3",
            "wall1.1.6x6.4",
            "wall1.1.6x6.5",
            "wall1.1.6x6.6",
            "wall1.1.6x3.1",
            "wall1.1.6x3.2",
            "wall1.1.6x3.3",
            "wall1.1.6x3.4",
            "wall1.1.6x3.5",
            "wall1.1.6x3.6",
            "wall1.1.3x6.1",
            "wall1.1.3x6.2",
            "wall1.1.3x6.3",
            "wall1.1.2x2.1",
            "wall1.1.2x2.2",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.1.1x2.1",
            "wall1.2.1x2.1",
            "wall1.1.6x6.7",
            "wall1.1.6x6.8",
            "wall1.1.6x6.9",
            "wall1.1.6x6.10",
            "wall1.1.6x6.11",
            "wall1.1.6x6.12",
            "wall1.1.6x3.7",
            "wall1.1.6x3.8",
            "wall1.1.6x3.9",
            "wall1.1.6x3.10",
            "wall1.1.6x3.11",
            "wall1.1.6x3.12",
            "wall1.1.3x6.4",
            "wall1.1.3x6.5",
            "wall1.1.3x6.6",
            "wall1.1.2x2.3",
            "wall1.1.2x2.4",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.1.1x2.2",
            "wall1.2.1x2.2",
            "wall1.1.6x6.13",
            "wall1.1.6x6.14",
            "wall1.1.6x6.15",
            "wall1.1.6x6.16",
            "wall1.1.6x6.17",
            "wall1.1.6x6.18",
            "wall1.1.6x3.13",
            "wall1.1.6x3.14",
            "wall1.1.6x3.15",
            "wall1.1.6x3.16",
            "wall1.1.6x3.17",
            "wall1.1.6x3.18",
            "wall1.1.3x6.7",
            "wall1.1.3x6.8",
            "wall1.1.3x6.9",
            "wall1.1",
            "wall1.2",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.2.2x1.1",
            "wall1.2.2x1.2",
            "wall1.1.6x6.19",
            "wall1.1.6x6.20",
            "wall1.1.6x6.21",
            "wall1.1.6x6.22",
            "wall1.1.6x6.23",
            "wall1.1.6x6.24",
            "wall1.1.3x3.1",
            "wall1.1.3x3.2",
            "wall1.1.3x3.3",
            "wall1.2.3x3.1",
            "wall1.2.3x3.2",
            "wall1.2.3x3.3",
            "wall1.1.3x6.10",
            "wall1.1.3x6.11",
            "wall1.1.3x6.12",
            "wall1.3",
            "wall1.4",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.1.6x6.25",
            "wall1.1.6x6.26",
            "wall1.1.6x6.27",
            "wall1.1.6x6.28",
            "wall1.1.6x6.29",
            "wall1.1.6x6.30",
            "wall1.1.3x3.4",
            "wall1.1.3x3.5",
            "wall1.1.3x3.6",
            "wall1.2.3x3.4",
            "wall1.2.3x3.5",
            "wall1.2.3x3.6",
            "wall1.1.3x6.13",
            "wall1.1.3x6.14",
            "wall1.1.3x6.15",
            "wall1.5",
            "wall1.6",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.1.6x6.31",
            "wall1.1.6x6.32",
            "wall1.1.6x6.33",
            "wall1.1.6x6.34",
            "wall1.1.6x6.35",
            "wall1.1.6x6.36",
            "wall1.1.3x3.7",
            "wall1.1.3x3.8",
            "wall1.1.3x3.9",
            "wall1.2.3x3.7",
            "wall1.2.3x3.8",
            "wall1.2.3x3.9",
            "wall1.1.3x6.16",
            "wall1.1.3x6.17",
            "wall1.1.3x6.18",
            "wall1.7",
            "wall1.8",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.3.2x1.1",
            "wall1.3.2x1.2",
            "wall1.2.6x6.1",
            "wall1.2.6x6.2",
            "wall1.2.6x6.3",
            "wall1.2.6x6.4",
            "wall1.2.6x6.5",
            "wall1.2.6x6.6",
            "wall1.2.6x3.1",
            "wall1.2.6x3.2",
            "wall1.2.6x3.3",
            "wall1.2.6x3.4",
            "wall1.2.6x3.5",
            "wall1.2.6x3.6",
            "wall1.2.3x6.1",
            "wall1.2.3x6.2",
            "wall1.2.3x6.3",
            "wall1.2.2x2.1",
            "wall1.2.2x2.2",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.3.1x2.1",
            "wall1.4.1x2.1",
            "wall1.2.6x6.7",
            "wall1.2.6x6.8",
            "wall1.2.6x6.9",
            "wall1.2.6x6.10",
            "wall1.2.6x6.11",
            "wall1.2.6x6.12",
            "wall1.2.6x3.7",
            "wall1.2.6x3.8",
            "wall1.2.6x3.9",
            "wall1.2.6x3.10",
            "wall1.2.6x3.11",
            "wall1.2.6x3.12",
            "wall1.2.3x6.4",
            "wall1.2.3x6.5",
            "wall1.2.3x6.6",
            "wall1.2.2x2.3",
            "wall1.2.2x2.4",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.3.1x2.2",
            "wall1.4.1x2.2",
            "wall1.2.6x6.13",
            "wall1.2.6x6.14",
            "wall1.2.6x6.15",
            "wall1.2.6x6.16",
            "wall1.2.6x6.17",
            "wall1.2.6x6.18",
            "wall1.2.6x3.13",
            "wall1.2.6x3.14",
            "wall1.2.6x3.15",
            "wall1.2.6x3.16",
            "wall1.2.6x3.17",
            "wall1.2.6x3.18",
            "wall1.2.3x6.7",
            "wall1.2.3x6.8",
            "wall1.2.3x6.9",
            "wall1.9",
            "wall1.10",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.4.2x1.1",
            "wall1.4.2x1.2",
            "wall1.2.6x6.19",
            "wall1.2.6x6.20",
            "wall1.2.6x6.21",
            "wall1.2.6x6.22",
            "wall1.2.6x6.23",
            "wall1.2.6x6.24",
            "wall1.3.3x3.1",
            "wall1.3.3x3.2",
            "wall1.3.3x3.3",
            "wall1.4.3x3.1",
            "wall1.4.3x3.2",
            "wall1.4.3x3.3",
            "wall1.2.3x6.10",
            "wall1.2.3x6.11",
            "wall1.2.3x6.12",
            "wall1.11",
            "wall1.12",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.2.6x6.25",
            "wall1.2.6x6.26",
            "wall1.2.6x6.27",
            "wall1.2.6x6.28",
            "wall1.2.6x6.29",
            "wall1.2.6x6.30",
            "wall1.3.3x3.4",
            "wall1.3.3x3.5",
            "wall1.3.3x3.6",
            "wall1.4.3x3.4",
            "wall1.4.3x3.5",
            "wall1.4.3x3.6",
            "wall1.2.3x6.13",
            "wall1.2.3x6.14",
            "wall1.2.3x6.15",
            "wall1.13",
            "wall1.14",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "wall1.2.6x6.31",
            "wall1.2.6x6.32",
            "wall1.2.6x6.33",
            "wall1.2.6x6.34",
            "wall1.2.6x6.35",
            "wall1.2.6x6.36",
            "wall1.3.3x3.7",
            "wall1.3.3x3.8",
            "wall1.3.3x3.9",
            "wall1.4.3x3.7",
            "wall1.4.3x3.8",
            "wall1.4.3x3.9",
            "wall1.2.3x6.16",
            "wall1.2.3x6.17",
            "wall1.2.3x6.18",
            "wall1.15",
            "wall1.16",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "ladder1.top.1",
            "rope1.top.1",
            "deco1.tl.1",
            "deco1.top.1",
            "deco1.top.2",
            "deco1.top.3",
            "deco1.tr.1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "ladder1.1",
            "rope1.1",
            "deco1.left.1",
            "deco1.top.4",
            "deco1.top.5",
            "deco1.top.6",
            "deco1.right.1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "ladder1.2",
            "rope1.2",
            "deco1.left.2",
            "deco1.top.7",
            "deco1.top.8",
            "deco1.top.9",
            "deco1.right.2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "ladder1.3",
            "rope1.3",
            "deco1.left.3",
            "deco1.bot.4",
            "deco1.bot.5",
            "deco1.bot.6",
            "deco1.right.3",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "ladder1.bot.1",
            "rope1.bot.2",
            "deco1.bl.1",
            "deco1.bot.1",
            "deco1.bot.2",
            "deco1.bot.3",
            "deco1.br.1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "deco1.bot.7",
            "deco1.bot.8",
            "deco1.bot.9",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "deco1.bot.10",
            "deco1.bot.11",
            "deco1.bot.12",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ########################################################
    ]

    zx.tile_load_arr(tex_name="16x16", width=16, height=16, arr=tiles)

def init_32x32():
    zx.tex_load(
            file="data/gfx/32x32.tga",
            name="32x32")

    tiles = [
            "exit1",
            "entrance1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
    ]

    zx.tile_load_arr(tex_name="32x32", width=32, height=32, arr=tiles)

def init_weapons_tiles():

    zx.tex_load(
            file="data/gfx/weapons.tga",
            name="weapons")

    tiles = [
            "sword1.1",
            "sword1_carry_anim.1",
            "sword1_carry_anim.2",
            "sword1_use_anim.1",
            "sword1_use_anim.2",
            "sword1_use_anim.3",
            "sword1_use_anim.4",
            "sword1_use_anim.5",
            "sword1_use_anim.6",
    ]

    zx.tile_load_arr(tex_name="weapons", width=48, height=48, arr=tiles)

init_text()
init_light()
init_16x16()
init_32x32()
init_weapons_tiles()
