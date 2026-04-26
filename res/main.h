std::string mainPage = R"HTMLHTML(
<!DOCTYPE html>
<html lang="zh">
<head>
<meta charset="UTF-8" />
<meta name="viewport" content="width=device-width, initial-scale=1.0"/>
<title>活动日历</title>


<link href="https://unpkg.com/fullcalendar@6.1.11/index.global.min.css" rel="stylesheet">
<script src="https://unpkg.com/fullcalendar@6.1.11/index.global.min.js"></script>

<script src="https://code.jquery.com/jquery-3.7.1.min.js"></script>

<style>
body {
    margin: 0;
    font-family: Arial, sans-serif;
    background: radial-gradient(circle at top, #1a1a2e, #0f0f1a);
    color: white;
}

#calendar {
    max-width: 1200px;
    margin: 20px auto;
    padding: 10px;
    background: rgba(255,255,255,0.05);
    border-radius: 16px;
    backdrop-filter: blur(10px);
}

.fc {
    color: white;
}

.fc-toolbar-title {
    font-size: 20px;
}

.fc-button {
    background: #6a5acd !important;
    border: none !important;
    border-radius: 8px !important;
}

.fc-button:hover {
    background: #7b68ee !important;
}

.fc-event {
    background: #6a5acd;
    border: none;
    border-radius: 8px;
    padding: 2px;
}

::-webkit-scrollbar {
    width: 6px;
}
::-webkit-scrollbar-thumb {
    background: #666;
    border-radius: 4px;
}
</style>
</head>

<body>

<div id="calendar"></div>

<script>
$(function () {

    const calendarEl = document.getElementById('calendar');

    function toISOTime(t) {
        if (!t) return null;
        // 2026-05-01-10-00-00 → 2026-05-01T10:00:00
        return t.replace(
            /(\d{4}-\d{2}-\d{2})-(\d{2})-(\d{2})-(\d{2})/,
            "$1T$2:$3:$4"
        );
    }

    function formatDisplayTime(t) {
        if (!t) return "-";
        return t.replace(
            /(\d{4}-\d{2}-\d{2})-(\d{2})-(\d{2})-(\d{2})/,
            "$1 $2:$3:$4"
        );
    }

    function openDetail(item) {

        let html = `
        <div id="modalMask" style="
            position:fixed;top:0;left:0;width:100%;height:100%;
            background:rgba(0,0,0,0.65);
            display:flex;justify-content:center;align-items:center;
            z-index:9999;">

            <div style="
                width:92%;max-width:520px;
                background:#1e1e2f;
                padding:20px;
                border-radius:16px;
                color:white;
                max-height:85vh;
                overflow-y:auto;">

                <h2>${item.title || "Untitled"}</h2>

                <p style="opacity:0.8;">
                    ${formatDisplayTime(item.start_time)} ~ ${formatDisplayTime(item.end_time)}
                </p>

                <hr style="border:0;border-top:1px solid #333;margin:10px 0;">

                <p><b>Location:</b> ${item.position || "N/A"}</p>

                <p><b>Introduction:</b><br>${item.introduction || "N/A"}</p>

                <p><b>Detail:</b><br>${item.detail || "N/A"}</p>

                <hr style="border:0;border-top:1px solid #333;margin:10px 0;">

                <p><b>Participants:</b> ${item.participant_number || "Unknown"}</p>

                <p><b>Conditions:</b> ${item.participant_condition || "None"}</p>

                <p><b>Reward:</b> ${item.reward || "None"}</p>

                <hr style="border:0;border-top:1px solid #333;margin:10px 0;">

                <p><b>Links</b></p>

                <p>Signup: ${
                    item.signup_url
                    ? `<a href="${item.signup_url}" target="_blank" style="color:#6a5acd;">Open</a>`
                    : "N/A"
                }</p>

                <p>Check-in: ${
                    item.checkin_url
                    ? `<a href="${item.checkin_url}" target="_blank" style="color:#6a5acd;">Open</a>`
                    : "N/A"
                }</p>

                <p>Check-out: ${
                    item.checkout_url
                    ? `<a href="${item.checkout_url}" target="_blank" style="color:#6a5acd;">Open</a>`
                    : "N/A"
                }</p>

                <div style="margin-top:20px;display:flex;flex-direction:column;gap:8px;">

                    <button id="signupBtn" style="
                        padding:10px;
                        border:none;
                        border-radius:10px;
                        background:#6a5acd;
                        color:white;
                        cursor:pointer;">
                        Sign up
                    </button>

                    <button id="closeModal" style="
                        padding:10px;
                        border:none;
                        border-radius:10px;
                        background:#444;
                        color:white;
                        cursor:pointer;">
                        Close
                    </button>

                </div>
            </div>
        </div>
        `;

        $("body").append(html);

        $("#signupBtn").on("click", function () {
            if (item.signup_url) window.open(item.signup_url, "_blank");
        });

        $("#closeModal").on("click", function () {
            $("#modalMask").remove();
        });
    }

    let calendar = new FullCalendar.Calendar(calendarEl, {

        initialView: 'timeGridWeek',
        locale: 'zh-cn',
        height: "auto",
        nowIndicator: true,

        headerToolbar: {
            left: 'prev,next today',
            center: 'title',
            right: 'timeGridWeek,timeGridDay'
        },

        events: function(fetchInfo, successCallback, failureCallback) {

            $.ajax({
                url: "/get",
                method: "POST",
                success: function(res) {
                    
                    let data = typeof res === "string" ? JSON.parse(res) : res;

                    let events = (data.content || []).map(item => ({
                        id: item.id,
                        title: item.title || "Untitled",
                        start: toISOTime(item.start_time),
                        end: toISOTime(item.end_time),
                        extendedProps: item
                    }));

                    successCallback(events);
                },
                error: function() {
                    failureCallback();
                }
            });
        },

        eventClick: function(info) {
            openDetail(info.event.extendedProps);
        }
    });

    calendar.render();

});
</script>

</body>
</html>
)HTMLHTML";
