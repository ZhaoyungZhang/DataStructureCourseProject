SEED = 10
NUM_CASES = 10

FIND = 1
INSERT = 2
DELETE = 3
DELETE_MIN = 4
DELETE_MAX = 5
OUTPUT = 6

save_path = './data'

TEST_CASES = [
    dict(
        allow_duplicate=False,
        op_num=100,
        init_size=100,
        op=[FIND, INSERT, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=100,
        init_size=100,
        op=[FIND, DELETE, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=100,
        init_size=100,
        op=[FIND, INSERT, DELETE_MIN, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=100,
        init_size=100,
        op=[FIND, INSERT, DELETE_MAX, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=100,
        init_size=100,
        op=[FIND, INSERT, DELETE, DELETE_MIN, DELETE_MAX, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=1000,
        init_size=100,
        op=[FIND, INSERT, DELETE, DELETE_MIN, DELETE_MAX, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=2000,
        init_size=100,
        op=[FIND, INSERT, DELETE, DELETE_MIN, DELETE_MAX, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=3000,
        init_size=100,
        op=[FIND, INSERT, DELETE, DELETE_MIN, DELETE_MAX, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=4000,
        init_size=100,
        op=[FIND, INSERT, DELETE, DELETE_MIN, DELETE_MAX, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=5000,
        init_size=100,
        op=[FIND, INSERT, DELETE, DELETE_MIN, DELETE_MAX, OUTPUT]
    ),
    dict(
        allow_duplicate=False,
        op_num=10000,
        init_size=100,
        op=[FIND, INSERT, DELETE, DELETE_MIN, DELETE_MAX, OUTPUT]
    )
]